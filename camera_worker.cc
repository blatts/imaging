// -*- mode: C++/lah -*-
// Time-stamp: "2010-03-03 14:23:11 srgang"

/*
  file       camera_worker.cc
  copyright  (c) Sebastian Blatt 2010
  url        http://wiki.havens.de

 */

#include "gui_ids.hh"
#include "camera.hh"
#include "camera_worker.hh"

#include <sstream>

DEFINE_EVENT_TYPE(wxEVT_CAMERA_DATA)

CameraWorker::CameraWorker(wxFrame* parent_,
                           message_queue_t* message_queue_,
                           message_queue_t* command_queue_,
                           wxMutex* message_queue_mutex_,
                           wxMutex* command_queue_mutex_,
                           long** raw_picture_data_,
                           wxMutex* raw_picture_data_mutex_,
                           CameraExperimentControl* experiment_control_,
                           wxMutex* experiment_control_mutex_
                          )
  : parent(parent_),
    message_queue(message_queue_),
    command_queue(command_queue_),
    message_queue_mutex(message_queue_mutex_),
    command_queue_mutex(command_queue_mutex_),
    raw_picture_data(raw_picture_data_),
    raw_picture_data_mutex(raw_picture_data_mutex_),
    camera(NULL),
    image_spool_path(IMAGE_SPOOL_PATH),
    experiment_control(experiment_control_),
    experiment_control_mutex(experiment_control_mutex_),
    save_images(false),
    using_kinetics(false),
    n_kinetics(0)
{
  camera = new Camera(this);
}

CameraWorker::~CameraWorker(){
  clear_command_queue();
  log_message("Shutting down camera");
  camera->Shutdown();
  // Sleep to see error messages, then shutdown
  std::ostringstream os;
  for(int i=SHUTDOWN_DELAY; i>0; --i){
    //os.str("");
    //os << "shutdown in " << i << " ...";
    //log_message(os.str());
    wxThread::Sleep(1000);
  }
  signal_parent(ID_CAMERA_WORKER_DONE);
  if(camera){
    delete camera;
    camera = NULL;
  }
}

void CameraWorker::signal_parent(int id, const std::string& msg){
  wxCommandEvent evt(wxEVT_COMMAND_MENU_SELECTED,id);
  if(msg!=""){
    evt.SetString(msg.c_str());
  }
  wxPostEvent(parent,evt);
}

void* CameraWorker::Entry(){
  std::ostringstream os;
  std::string cmd = "";
  int i=0;

  log_message("Starting camera");
  if(!camera->Initialize()){
    log_error("Camera initialization failed");
    goto error;
  }
  log_message("Allocating image memory");
  {
    wxMutexLocker lock(*raw_picture_data_mutex);
    int n = camera->GetImageArea();
    *raw_picture_data = new long[n];
    memset(*raw_picture_data,0,n*sizeof(long));
  }

  while(true){
    {
      wxMutexLocker lock(*command_queue_mutex);
      if(command_queue->size()){
        cmd = command_queue->front();
        command_queue->pop();
      }
    }
    if(cmd != ""){
      if(cmd == "QUIT"){
        break;
      }
      else if(cmd == "TEMP?"){
        int t = camera->GetTemperature();
        wxCommandEvent evt = wxCommandEvent(wxEVT_CAMERA_DATA,ID_CAMERA_WORKER);
        os << "TEMP:" << t << " C";
        evt.SetString(os.str().c_str()); os.str("");
        wxPostEvent(parent,evt);
      }
      else if(cmd == "START"){
        if(!update_camera_control(true)){
          goto error;
        }
        update_experiment_timestamp();
        signal_experiment_begin();

        // Continue taking pictures until aborted by user

        bool aborted=false;
        while(!aborted){ // aborted gets signaled in experiment loop
          if(check_for_interrupt()){ // aborted.
            break;
          }

          // Start experiment and wait for image
          camera->StartExperiment();
          while(!aborted){
            i = camera->GetStatus();
            if(i == 3){ // success!
              //log_message("Acquisition successful");
              break;
            }
            else if(i == 2) { // still acquiring
              //log_message("Still acquiring");

              // Check whether user aborted while camera is waiting
              wxThread::Sleep(50);
              aborted = check_for_interrupt();
            }
            else{ //something is wrong
              log_error("Acquisition failed");
              break;
            }
          } // end of wait for image loop
          if(aborted){
            break;
          }


          //log_message("Download raw image data from camera");
          bool dlworked = false, saveworked=false;
          std::string filestamp = get_timestamp_file();
          std::string imgpath = get_timestamp_path(filestamp);
          { // Download image data
            wxMutexLocker lock(*raw_picture_data_mutex);
            dlworked = camera->DownloadImage(raw_picture_data);
            if(dlworked && save_images){
              saveworked = camera->SaveLastImageTIFF(imgpath);
            }
          }
          if(!dlworked){
            log_error("Failed downloading image from camera");
            break;
          }

          if(save_images){
            if(saveworked){
              os << "Image -> \"" << imgpath << "\"";
              log_message(os.str()); os.str("");
              signal_image_ready(using_kinetics?n_kinetics:1,imgpath);
            }
            else{
              os << "Failed saving image to \"" << imgpath << "\"";
              log_error(os.str()); os.str("");
              break;
            }
          }
          else{ // not saved to disk, but need to update image window
            signal_image_ready(using_kinetics?n_kinetics:1);
          }
        } // end of experiment loop
        signal_experiment_end();
      }
      else if(cmd == "INT:ABORT"){
        log_message("ABORT futile, camera not running");
      }
      else if(cmd == "INT:CTL"){
        log_message("CTL update handled on experiment start");
      }
      else{
        os << "Camera thread : do not know how to handle command \""
           << cmd << "\"";
        log_message(os.str()); os.str("");
      }
      cmd = "";
    }
    else{
      wxThread::Sleep(20);
    }
  }

  goto exit;
error:
  log_error("Fatal error, aborting camera thread.");
exit:
  return NULL;
}

// Check for interrupt commands on the command queue (indicated by
// prefix INT:). If INT:ABORT, return true to signal stop. Otherwise
// handle interrupt here and ignore every regular command.
bool CameraWorker::check_for_interrupt(){
  bool abortq = false;
  { // Check for interrupts on the message queue
    wxMutexLocker lock(*command_queue_mutex);
    while(command_queue->size()){
      std::string c = command_queue->front();
      if(c == "QUIT"){
        camera->AbortExperiment();
        abortq = true;
        break;
      }
      if(c.substr(0,4) == "INT:"){
        c = c.substr(4);
        if(c == "ABORT"){
          camera->AbortExperiment();
          abortq = true;
        }
        else if(c == "CTL"){
          update_camera_control(false);
        }
        else{
          log_message("Unhandled interrupt :\""+c+"\"");
        }
        command_queue->pop();
      }
      else{
        // ignore everything else
        command_queue->pop();
      }
    }
  }
  return abortq;
}

void CameraWorker::clear_command_queue(){
  { // clear command queue
    wxMutexLocker lock(*command_queue_mutex);
    while(!command_queue->empty()){
      command_queue->pop();
    }
  }
}

// Update internal variables from CameraExperimentControl. If
// setup_experiment, also call camera->SetupExperiment(). Return value
// indicates whether everything worked.
bool CameraWorker::update_camera_control(bool setup_experiment){
  bool rc = true;
  { // Setup experiment with data from CameraExperimentControl
    wxMutexLocker lock(*experiment_control_mutex);
    if(setup_experiment){
      using_kinetics = experiment_control->kinetics_mode;
      n_kinetics = experiment_control->number_kinetics;
      rc = camera->SetupExperiment(experiment_control->exposure_time,
                                   experiment_control->shutter_mode,
                                   experiment_control->internal_trigger,
                                   experiment_control->kinetics_mode,
                                   experiment_control->number_kinetics
                                  );
      if(!rc) {
        log_error("Camera Experiment Setup failed");
      }
    }
    if(rc){
      if(save_images != experiment_control->save_images){
        std::ostringstream os;
        if(experiment_control->save_images){
          update_experiment_timestamp();
          os << "Saving images now, updated experimental run timestamp to "
             << experiment_timestamp;
        }
        else{
          os << "Stopped saving images";
        }
        log_message(os.str());
      }
      save_images = experiment_control->save_images;
      image_spool_path = experiment_control->image_spool_path.c_str();
    }
  }
  return rc;
}



void CameraWorker::log_message(const std::string& msg){
  {
    wxMutexLocker lock(*message_queue_mutex);
    message_queue->push(msg);
  }
  signal_parent(ID_NEW_CHILD_MESSAGE);
}

void CameraWorker::log_error(const std::string& msg){
  {
    wxMutexLocker lock(*message_queue_mutex);
    message_queue->push(msg);
  }
  signal_parent(ID_NEW_CHILD_ERROR);
}

void CameraWorker::signal_experiment_begin(){
  signal_parent(ID_CAMERA_EXPERIMENT_BEGIN,experiment_timestamp.c_str());
}

void CameraWorker::signal_experiment_end(){
  std::ostringstream os;
  os << image_spool_path << "\\" << experiment_timestamp << "_*.tif_*";
  signal_parent(ID_CAMERA_EXPERIMENT_END,os.str());
}

void CameraWorker::signal_image_ready(size_t n_images, const std::string& locator){
  std::ostringstream os;
  os << locator << ";" << n_images;
  signal_parent(ID_CAMERA_IMAGE_READY,os.str());
}

std::string CameraWorker::get_timestamp_file(){
  std::ostringstream os;
  os << IMAGE_NAME_FORMAT << ".tif";
  return wxDateTime::Now().Format(os.str().c_str()).c_str();
}

std::string CameraWorker::get_timestamp_path(const std::string& timestamp_file){
  std::ostringstream os;
  os << image_spool_path << "\\" << experiment_timestamp << "_"
     << timestamp_file;
  return os.str().c_str();
}

void CameraWorker::update_experiment_timestamp(){
  experiment_timestamp = wxDateTime::Now().Format("%y%m%d-%H%M%S");
  //wxMkdir(image_spool_path + "\\" + experiment_timestamp);
}


// camera_worker.cc ends here
