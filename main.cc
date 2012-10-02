// -*- mode: C++/lah -*-
// Time-stamp: "2012-10-02 15:09:15 sb"

/*
  file       main.cc
  copyright  (c) Sebastian Blatt 2010, 2011, 2012

 */

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/log.h>
#include <wx/thread.h>
#include <wx/aboutdlg.h>
#include <iostream>
#include <queue>
#include <string>
#include <map>

#include "gui_ids.hh"
#include "image_window.hh"
#include "camera_worker.hh"
#include "camera_control.hh"
#include "file_sorter.hh"

#define PROGRAM  "Sr Imaging"
#define VERSION  "20121002"
#define DESC     "Fast image acquisition and data storage."
#define COPY     "Copyright (c) Sebastian Blatt 2010, 2011, 2012"
#define LICENSE  "This program is licensed to you under a Creative Commons Attribution-ShareAlike 3.0 " \
                 "Unported License. Please see http://creativecommons.org/licenses/by-sa/3.0/legalcode for details."

#define MAIN_FRAME_X_POSITION  0
#define MAIN_FRAME_Y_POSITION  0
#define MAIN_FRAME_WIDTH       480
#define MAIN_FRAME_HEIGHT      640

#define FILE_SORTER_TARGET_DIRECTORY "z:\\Sr3\\data"

#define IMAGE_FRAME_X_POSITION  0
#define IMAGE_FRAME_Y_POSITION  0
#define IMAGE_FRAME_WIDTH       1033
#define IMAGE_FRAME_HEIGHT      1050

// do not change this for now
#define IMAGE_WIDTH  1024
#define IMAGE_HEIGHT 1024

#define TEMPERATURE_TIMER_PERIOD_MS 5000

// ---------------------------------------------------------------------- Classes

class SRIMainFrame;
class SRIApp : public wxApp {
  private:
    SRIMainFrame* frame;
  public:
    virtual bool OnInit();
};

IMPLEMENT_APP(SRIApp)

typedef std::map<std::string,wxControl*> control_map_t;

class SRIMainFrame : public wxFrame{
  private:
    CameraWorker* camera;
    bool camera_active;
    message_queue_t message_queue;
    message_queue_t camera_command_queue;
    wxMutex message_queue_mutex;
    wxMutex camera_command_queue_mutex;
    long* raw_image_data;
    wxMutex raw_image_data_mutex;
    CameraExperimentControl experiment_control;
    wxMutex experiment_control_mutex;
    FileSorterWorker* sorter;
    bool sorter_active;
    message_queue_t sorter_command_queue;
    wxMutex sorter_command_queue_mutex;
    std::string sorter_target_directory;

    wxNotebook* tab_ctrl;
    wxLogTextCtrl* log;
    ImageFrame* img_frame;
    control_map_t control_map;

    wxTimer temperature_timer;

  public:
    SRIMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~SRIMainFrame();

    void StartCameraWorker();
    void StartFileSorterWorker();

    void OnQuit(wxCommandEvent&);
    void OnClose(wxCloseEvent&);
    void OnCmdBeginExperiment(wxCommandEvent&);
    void OnCmdAbortExperiment(wxCommandEvent&);
    void OnCmdScaleNextImage(wxCommandEvent&);

    void OnNewChildMessage(wxCommandEvent&);
    void OnNewChildError(wxCommandEvent&);

    void OnCameraWorkerDone(wxCommandEvent&);
    void OnCameraExperimentBegin(wxCommandEvent& evt);
    void OnCameraExperimentEnd(wxCommandEvent& evt);
    void OnCameraData(wxCommandEvent& evt);
    void OnCameraImageReady(wxCommandEvent& evt);

    void OnChangeInterruptField(wxCommandEvent&);

    void OnTemperatureTimer(wxTimerEvent&);

    void OnFileSorterWorkerDone(wxCommandEvent&);

    void OnAbout(wxCommandEvent&);

  private:
    wxPanel* CreateMainPanel();
    wxPanel* CreateSetupPanel();
    void dispatch_camera_command(const std::string& cmd);
    void dispatch_filesorter_command(const std::string& cmd);
    void read_back_data_from_controls();


    DECLARE_EVENT_TABLE()
};

// --------------------------------------------------------------- Implementation


BEGIN_EVENT_TABLE(SRIMainFrame, wxFrame)
EVT_MENU(ID_QUIT, SRIMainFrame::OnQuit)
EVT_CLOSE(SRIMainFrame::OnClose)
EVT_MENU(ID_NEW_CHILD_MESSAGE, SRIMainFrame::OnNewChildMessage)
EVT_MENU(ID_NEW_CHILD_ERROR, SRIMainFrame::OnNewChildError)
EVT_MENU(ID_CAMERA_WORKER_DONE, SRIMainFrame::OnCameraWorkerDone)
EVT_MENU(ID_CAMERA_EXPERIMENT_BEGIN, SRIMainFrame::OnCameraExperimentBegin)
EVT_MENU(ID_CAMERA_EXPERIMENT_END, SRIMainFrame::OnCameraExperimentEnd)
EVT_MENU(ID_CAMERA_IMAGE_READY, SRIMainFrame::OnCameraImageReady)
EVT_COMMAND(ID_CAMERA_WORKER, wxEVT_CAMERA_DATA, SRIMainFrame::OnCameraData)
EVT_TIMER(ID_TEMPERATURE_TIMER,SRIMainFrame::OnTemperatureTimer)
EVT_BUTTON(ID_CMD_BEGIN_EXPERIMENT,SRIMainFrame::OnCmdBeginExperiment)
EVT_BUTTON(ID_CMD_ABORT_EXPERIMENT,SRIMainFrame::OnCmdAbortExperiment)
EVT_BUTTON(ID_CMD_SCALE_NEXT_IMAGE,SRIMainFrame::OnCmdScaleNextImage)
EVT_MENU(ID_FILE_SORTER_WORKER_DONE, SRIMainFrame::OnFileSorterWorkerDone)
EVT_MENU(ID_ABOUT, SRIMainFrame::OnAbout)
END_EVENT_TABLE()




// Application

bool SRIApp::OnInit(){
  frame = new SRIMainFrame(wxString(PROGRAM)+_(" version ")+wxString(VERSION),
                           wxPoint(MAIN_FRAME_X_POSITION, MAIN_FRAME_Y_POSITION),
                           wxSize(MAIN_FRAME_WIDTH, MAIN_FRAME_HEIGHT));
  frame->StartCameraWorker();
  frame->StartFileSorterWorker();
  return true;
}


// Main Frame

SRIMainFrame::SRIMainFrame(const wxString& title,
                           const wxPoint& pos,
                           const wxSize& size)
  : wxFrame(NULL,-1,title,pos,size),
    camera(NULL),
    camera_active(false),
    raw_image_data(NULL),
    tab_ctrl(NULL),
    log(NULL),
    img_frame(NULL),
    temperature_timer(this,ID_TEMPERATURE_TIMER),
    sorter_active(false),
    sorter_target_directory(FILE_SORTER_TARGET_DIRECTORY)
{
  // Create a menu
  wxMenu* m = new wxMenu;
  m->AppendSeparator();
  m->Append(ID_QUIT, _("E&xit"));
  wxMenu* m2 = new wxMenu;
  m2->Append(ID_ABOUT,_("&About"));
  wxMenuBar* mbar = new wxMenuBar;
  mbar->Append(m,_("&File"));
  mbar->Append(m2,_("&Help"));
  SetMenuBar(mbar);

  // Create status bar
  CreateStatusBar(3);
  SetStatusText("",0);
  SetStatusText("",1);
  SetStatusText("",2);

  // Tab control
  tab_ctrl = new wxNotebook(this,wxID_ANY);
  tab_ctrl->AddPage(CreateMainPanel(),"Main",true);
  tab_ctrl->AddPage(CreateSetupPanel(),"Setup",false);

  Show(true);

  wxLogMessage(_("%s version %s, %s"), PROGRAM, VERSION, COPY);

  // Setup image frame
  img_frame = new ImageFrame(this, _("Image"),
                             wxPoint(IMAGE_FRAME_X_POSITION, IMAGE_FRAME_Y_POSITION),
                             wxSize(IMAGE_FRAME_WIDTH,IMAGE_FRAME_HEIGHT),
                             &raw_image_data, &raw_image_data_mutex,
                             IMAGE_WIDTH, IMAGE_HEIGHT);
  img_frame->Show(true);
}

SRIMainFrame::~SRIMainFrame(){
  {
    wxMutexLocker lock(raw_image_data_mutex);
    if(raw_image_data){
      delete[] raw_image_data;
      raw_image_data = NULL;
    }
  }
}


wxPanel* SRIMainFrame::CreateMainPanel(){
  wxPanel* p = new wxPanel(tab_ctrl);

  wxBoxSizer* border_sizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* ctrl_sizer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* log_sizer = new wxBoxSizer(wxHORIZONTAL);
  wxFlexGridSizer* setting_sizer = new wxFlexGridSizer(6,10,5); // cols, hgap, vgap
  setting_sizer->AddGrowableCol(1);
  setting_sizer->AddGrowableCol(3);
  setting_sizer->AddGrowableCol(5);

  // Fields: type, identifier, label, initial value, interrupt?
  const char* labels[] = {"bool","scale_manual","Manual scale?","false","true",
                          "text","scale_min","Scale min","0","true",
                          "text","scale_max","Scale max","1","true",
                          "bool","kinetics_mode","Kinetics mode?","true","false",
                          "bool","process_kinetics","Process kinetics?","false","true",
                          "bool","internal_trigger","Internal Trigger?","false","false",
                          "bool","save_images","Save Images?","false","true"
    };
  size_t nlabels = 7;
  size_t nfields = 5;
  for(size_t i=0; i<nlabels; ++i){
    wxStaticText* lbl =  new wxStaticText(p,wxNewId(),
                                          labels[nfields*i]!=wxString("bool")?labels[nfields*i+2]:"");
    wxControl* cmd = NULL;
    wxString type = labels[nfields*i];
    int id = wxNewId();
    if(type=="text") {
      cmd = new wxTextCtrl(p,id,labels[nfields*i+3]);
      // If variable controlled by control needs to update during experiment,
      // bind it to OnChangeInterruptField
      if(labels[nfields*i+4]==wxString("true")){
        Connect(id,wxEVT_COMMAND_TEXT_UPDATED,
                wxCommandEventHandler(SRIMainFrame::OnChangeInterruptField));
      }
    }
    else if(type=="bool"){
      wxCheckBox* q = new wxCheckBox(p,id,labels[nfields*i+2],wxDefaultPosition,
                                     wxDefaultSize,wxALIGN_RIGHT);
      q->SetValue(labels[nfields*i+3]==wxString("true"));
      cmd = q;
      if(labels[nfields*i+4]==wxString("true")){
        Connect(id,wxEVT_COMMAND_CHECKBOX_CLICKED,
                wxCommandEventHandler(SRIMainFrame::OnChangeInterruptField));
      }
    }
    control_map[labels[nfields*i+1]] = cmd;
    setting_sizer->Add(lbl,0,wxALIGN_RIGHT|wxALIGN_TOP);
    setting_sizer->Add(cmd,1,wxEXPAND);
  }

  wxButton* b_start_exp = new wxButton(p,ID_CMD_BEGIN_EXPERIMENT,"Start Camera");
  wxButton* b_abort_exp = new wxButton(p,ID_CMD_ABORT_EXPERIMENT,"Stop Camera");
  wxButton* b_scale_to_next_image = new wxButton(p,ID_CMD_SCALE_NEXT_IMAGE,"Autoscale Next Image");
  ctrl_sizer->Add(b_start_exp,1,wxALL);
  ctrl_sizer->Add(b_abort_exp,1,wxALL);
  ctrl_sizer->Add(b_scale_to_next_image,1,wxALL);


  wxTextCtrl* q = new wxTextCtrl(p,wxNewId(),"",wxDefaultPosition,wxDefaultSize,
                                 wxTE_MULTILINE|wxTE_READONLY|wxHSCROLL);
  log = new wxLogTextCtrl(q);
  wxLog::SetActiveTarget(log);
  log_sizer->Add(q,1,wxALL|wxEXPAND);

  border_sizer->Add(ctrl_sizer,1,wxALL|wxEXPAND,10);
  border_sizer->Add(setting_sizer,3,wxALL|wxEXPAND,10);
  border_sizer->Add(log_sizer,2,wxALL|wxEXPAND);
  p->SetSizer(border_sizer);
  border_sizer->Fit(p);

  return p;
}

wxPanel* SRIMainFrame::CreateSetupPanel(){
  wxPanel* p = new wxPanel(tab_ctrl);

  wxBoxSizer* border_sizer = new wxBoxSizer(wxVERTICAL);
  wxFlexGridSizer* setting_sizer = new wxFlexGridSizer(4,10,5); // cols, hgap, vgap
  setting_sizer->AddGrowableCol(1);
  setting_sizer->AddGrowableCol(3);
  const char* labels[] = {"exposure_time","Exposure time (ms)","0.05",
                          "number_kinetics","Number of kinetics images", "3",
                          "image_spool_path","Image spool directory",IMAGE_SPOOL_PATH
    };
  size_t nlabels = 3;
  for(size_t i=0; i<nlabels; ++i){
    wxStaticText* lbl = new wxStaticText(p,wxNewId(),labels[3*i+1]+wxString(": "));
    wxTextCtrl* cmd = new wxTextCtrl(p,wxNewId(),labels[3*i+2]);
    control_map[labels[3*i]] = cmd;
    setting_sizer->Add(lbl,0,wxALIGN_RIGHT|wxALIGN_TOP);
    setting_sizer->Add(cmd,1,wxEXPAND);
  }

  border_sizer->Add(setting_sizer,1,wxALL|wxEXPAND,10);
  p->SetSizer(border_sizer);
  border_sizer->Fit(p);

  return p;
}


void SRIMainFrame::OnNewChildMessage(wxCommandEvent&){
  wxMutexLocker lock(message_queue_mutex);
  size_t n = message_queue.size();
  for(size_t i=0; i<n; ++i){
    wxLogMessage(message_queue.front().c_str());
    message_queue.pop();
  }
}

void SRIMainFrame::OnNewChildError(wxCommandEvent&){
  wxMutexLocker lock(message_queue_mutex);
  size_t n = message_queue.size();
  for(size_t i=0; i<n; ++i){
    wxLogError(message_queue.front().c_str());
    message_queue.pop();
  }
}


void SRIMainFrame::StartCameraWorker(){
  // Camera worker thread
  camera = new CameraWorker(this,&message_queue,&camera_command_queue,
                            &message_queue_mutex,&camera_command_queue_mutex,
                            &raw_image_data,&raw_image_data_mutex,
                            &experiment_control,&experiment_control_mutex
                           );
  if(camera->Create() != wxTHREAD_NO_ERROR){
    wxLogError("Cannot create camera worker thread!");
  }
  camera->Run();
  camera_active = true;
  // start temperature timer
  temperature_timer.Start(TEMPERATURE_TIMER_PERIOD_MS);
  wxLogMessage("Temperature timer started");
}

void SRIMainFrame::StartFileSorterWorker(){
  // File sorter worker thread
  sorter = new FileSorterWorker(this,&message_queue,&message_queue_mutex,
                                &sorter_command_queue,&sorter_command_queue_mutex,
                                sorter_target_directory
                               );
  if(sorter->Create() != wxTHREAD_NO_ERROR){
    wxLogError("Cannot create file sorter worker thread!");
  }
  sorter->Run();
  sorter_active = true;
}

void SRIMainFrame::OnQuit(wxCommandEvent&){
  if(camera_active){
    dispatch_camera_command("QUIT");
  }
  if(sorter_active){
    dispatch_filesorter_command("QUIT");
  }
  if(!camera_active && !sorter_active){
    Close(true);
  }
}

void SRIMainFrame::OnClose(wxCloseEvent&){
  if(camera_active){
    dispatch_camera_command("QUIT");
  }
  if(sorter_active){
    dispatch_filesorter_command("QUIT");
  }
  if(!camera_active && !sorter_active){
    Destroy();
  }
}

void SRIMainFrame::OnCmdBeginExperiment(wxCommandEvent&){
  read_back_data_from_controls();
  // autoscale to initial picture
  img_frame->SetScaleNextImage();
  dispatch_camera_command("START");
}

void SRIMainFrame::OnCmdAbortExperiment(wxCommandEvent&){
  dispatch_camera_command("INT:ABORT");
}

void SRIMainFrame::OnCmdScaleNextImage(wxCommandEvent&){
  if(img_frame){
    wxLogMessage("Autoscaling to next Image.");
    img_frame->SetScaleNextImage();
  }
}


void SRIMainFrame::OnCameraWorkerDone(wxCommandEvent&){
  camera_active = false;
  wxLogMessage("Camera worker thread finished");
  // stop temperature timer
  temperature_timer.Stop();
  wxLogMessage("Temperature timer stopped");
  wxCommandEvent evt(wxEVT_COMMAND_MENU_SELECTED,ID_QUIT);
  wxPostEvent(this,evt);
}

void SRIMainFrame::OnCameraExperimentBegin(wxCommandEvent& evt){
  wxLogMessage("Experiment started at "+evt.GetString());
}

void SRIMainFrame::OnCameraExperimentEnd(wxCommandEvent& evt){
  wxLogMessage("Experiment ended.");
  dispatch_filesorter_command(std::string("CLEANUP:")+evt.GetString().c_str());
}

void SRIMainFrame::OnCameraData(wxCommandEvent& evt){
  wxString s = evt.GetString();
  if(s.StartsWith("TEMP:")){
    SetStatusText("CCD Temperature : "+s.Mid(5),2);
  }
  else{
    wxLogMessage("Unhandled Camera data event: "+evt.GetString());
  }
}

void SRIMainFrame::OnCameraImageReady(wxCommandEvent& evt){
  //wxLogMessage("Image ready");
  img_frame->UpdateData();
  wxString loc = evt.GetString();
  if(loc.Mid(0,1)!=";"){
    dispatch_filesorter_command(std::string("SORT:")+loc.c_str());
  }
}


void SRIMainFrame::OnChangeInterruptField(wxCommandEvent&){
  //wxLogMessage("OnChangeInterruptField %d",evt.GetId());
  read_back_data_from_controls();
  if(camera_active){
    dispatch_camera_command("INT:CTL");
  }
}


void SRIMainFrame::OnTemperatureTimer(wxTimerEvent&){
  if(camera_active){
    dispatch_camera_command("TEMP?");
  }
}

void SRIMainFrame::dispatch_camera_command(const std::string& cmd){
  wxMutexLocker lock(camera_command_queue_mutex);
  camera_command_queue.push(cmd);
}

void SRIMainFrame::dispatch_filesorter_command(const std::string& cmd){
  wxMutexLocker lock(sorter_command_queue_mutex);
  sorter_command_queue.push(cmd);
}

void SRIMainFrame::read_back_data_from_controls(){
  double t = 0;
  unsigned long i=0;
  wxString s;
  bool b = false;

  // Update Experimental control data structure
  { // read back data from controls
    wxMutexLocker lock(experiment_control_mutex);

    s = reinterpret_cast<wxTextCtrl*>(control_map["exposure_time"])->GetValue();
    if(s.ToDouble(&t)){
      experiment_control.exposure_time = (float)(t * 1e-3);
    }
    s = reinterpret_cast<wxTextCtrl*>(control_map["image_spool_path"])->GetValue();
    experiment_control.image_spool_path = s;
    b = reinterpret_cast<wxCheckBox*>(control_map["save_images"])->GetValue();
    experiment_control.save_images = b;
    b = reinterpret_cast<wxCheckBox*>(control_map["kinetics_mode"])->GetValue();
    experiment_control.kinetics_mode = b;
    b = reinterpret_cast<wxCheckBox*>(control_map["internal_trigger"])->GetValue();
    experiment_control.internal_trigger = b;
    s = reinterpret_cast<wxTextCtrl*>(control_map["number_kinetics"])->GetValue();
    if(s.ToULong(&i)){
      experiment_control.number_kinetics = (unsigned int)i;
    }
    b = reinterpret_cast<wxCheckBox*>(control_map["process_kinetics"])->GetValue();
    experiment_control.process_kinetics = b;
    if(experiment_control.process_kinetics){
      img_frame->SetKinetics(true,experiment_control.number_kinetics);
    }
    else{
      img_frame->SetKinetics(false,1);
    }
  }

  // Update the rest
  b = reinterpret_cast<wxCheckBox*>(control_map["scale_manual"])->GetValue();
  s = reinterpret_cast<wxTextCtrl*>(control_map["scale_min"])->GetValue();
  if(s.ToDouble(&t)){
    img_frame->SetScaleMin(t);
  }
  s = reinterpret_cast<wxTextCtrl*>(control_map["scale_max"])->GetValue();
  if(s.ToDouble(&t)){
    img_frame->SetScaleMax(t);
  }
  if(b != img_frame->GetScaleManual()){
    img_frame->SetScaleManual(b);
    if(!b){
      // Autoscale to next image if manual scaling deselected
      img_frame->SetScaleNextImage();
    }
  }
}

void SRIMainFrame::OnFileSorterWorkerDone(wxCommandEvent&){
  sorter_active = false;
  wxLogMessage("File sorter worker thread finished");
  wxCommandEvent evt(wxEVT_COMMAND_MENU_SELECTED,ID_QUIT);
  wxPostEvent(this,evt);
}

void SRIMainFrame::OnAbout(wxCommandEvent&){
  wxAboutDialogInfo info;
  info.SetName(PROGRAM);
  info.SetVersion(VERSION);
  info.SetDescription(DESC);
  info.SetCopyright(COPY);
  info.SetLicense(LICENSE);
  wxAboutBox(info);
}




// main.cc ends here
