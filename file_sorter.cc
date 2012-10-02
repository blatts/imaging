// -*- mode: C++/lah -*-
// Time-stamp: "2010-01-29 12:00:26 srgang"

/*
  file       file_sorter.cc
  copyright  (c) Sebastian Blatt 2010
  url        http://wiki.havens.de

 */

#include "gui_ids.hh"
#include "file_sorter.hh"
#include <sstream>
#include <wx/filename.h>
#include <wx/file.h>
#include <wx/dir.h>

DEFINE_EVENT_TYPE(wxEVT_FILE_SORTER)

FileSorterWorker::FileSorterWorker(wxFrame* parent_,
                                   message_queue_t* message_queue_,
                                   wxMutex* message_queue_mutex_,
                                   message_queue_t* command_queue_,
                                   wxMutex* command_queue_mutex_,
                                   const std::string target_directory_
                                  )
: parent(parent_),
  message_queue(message_queue_),
  message_queue_mutex(message_queue_mutex_),
  command_queue(command_queue_),
  command_queue_mutex(command_queue_mutex_),
  target_directory(target_directory_)
{
}

FileSorterWorker::~FileSorterWorker(){
}

void FileSorterWorker::signal_parent(int id){
  wxCommandEvent evt(wxEVT_COMMAND_MENU_SELECTED,id);
  wxPostEvent(parent,evt);
}

void FileSorterWorker::log_message(const std::string& msg){
  {
    wxMutexLocker lock(*message_queue_mutex);
    message_queue->push(msg);
  }
  signal_parent(ID_NEW_CHILD_MESSAGE);
}

void FileSorterWorker::log_error(const std::string& msg){
  {
    wxMutexLocker lock(*message_queue_mutex);
    message_queue->push(msg);
  }
  signal_parent(ID_NEW_CHILD_ERROR);
}


void* FileSorterWorker::Entry(){
  std::ostringstream os;
  std::string cmd;
  wxFile f1, f2;
  wxFileOffset l;
  void* buf = NULL;

  log_message("Starting file sorter");
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
      else if(cmd.substr(0,8) == "CLEANUP:"){
        cmd = cmd.substr(8);
        wxFileName f(cmd.c_str());
        wxString dir = f.GetPath();
        wxString glob = f.GetName()+f.GetExt();
        wxArrayString files;
        size_t n = wxDir::GetAllFiles(dir,&files,glob,wxDIR_FILES);
        log_message(std::string("Cleanup: \"")+cmd+"\"");
        for(size_t i=0; i<n; ++i){
          if(!wxRemoveFile(files[i])){
            os << "Failed removing file \"" << files[i] << "\"";
            goto error;
          }
        }
      }
      else if(cmd.substr(0,5) == "SORT:"){
        wxString c = cmd.substr(5);
        unsigned long frames = 1;
        int p = c.Find(';',true);
        //os << "sort:\"" << c << "\", p=" << p;
        //log_message(os.str()); os.str("");
        size_t i=0;
        if(p != wxNOT_FOUND){
          if(!c.Mid(p+1).ToULong(&frames)){
            frames = 1;
          }
          c = c.Mid(0,p);
        }

        wxFileName f(c);
        wxString n = f.GetName();
        wxString run = n.Mid(7,6);
        wxString file = n.Mid(21,6);
        wxString dirdate = target_directory + "\\" + n.Mid(0,6);
        wxString rundir = dirdate + "\\" + run;
        wxString infile = c + "_%d";
        wxString tofile = rundir+"\\" + file + "_%d." + f.GetExt();

        if(!wxDirExists(target_directory.c_str())){
          os << "Base directory \"" << target_directory << "\" does not exist";
          goto error;
        }
        if(!wxDirExists(dirdate)){
          if(!wxMkdir(dirdate)){
            os << "Failed creating directory \"" << dirdate.c_str() << "\"";
            goto error;
          }
        }
        if(!wxDirExists(rundir)){
          if(!wxMkdir(rundir)){
            os << "Failed creating directory \"" << rundir.c_str() << "\"";
            goto error;
          }
        }

        /* Do not use wxCopyFile or Win32::CopyFile since these work
           asynchronously and fail when copying many large files over
           the network. Instead do the naive thing and copy by hand.
        */

        for(i=0; i<frames; ++i){
          if(!f1.Open(wxString::Format(infile,i),wxFile::read)){
            os << "Failed opening \"" << wxString::Format(infile,i).c_str()
               << "\" for reading";
            goto error;
          }
          l = f1.Length();
          if(!f2.Open(wxString::Format(tofile,i),wxFile::write)){
            os << "Failed opening \"" << wxString::Format(tofile,i).c_str()
               << "\" for writing";
            goto error;
          }
          buf = (void*)malloc(sizeof(char)*l);
          if(f1.Read(buf,l)!=l){
            os << "Failed reading complete file \""
               << wxString::Format(infile,i).c_str() << "\"";
            goto error;
          }
          f1.Close();
          if(f2.Write(buf,l)!=l){
            os << "Failed writing complete file \""
               << wxString::Format(tofile,i).c_str() << "\"";
            goto error;
          }
          free(buf); buf = NULL;
          f2.Close();
        }

        /* Another cache problem. When calling wxRemoveFile here, the
           file disappears too fast for some of the copying above.

           if(!wxRemoveFile(c)){
             os << "Failed removing \"" << c << "\""; goto error;
           }

           Instead, implemented cleanup action when a run is done and
           sorted completely.
        */

        os << "Sort: \"" <<  infile << "\" \"" << tofile << "\", "
           << frames << " frames";
        log_message(os.str()); os.str("");
//         os << "dirdate: \"" << dirdate << "\"";
//         log_message(os.str()); os.str("");
//         os << "rundir: \"" << rundir << "\"";
//         log_message(os.str()); os.str("");
      }
    }
    cmd = "";
    wxThread::Sleep(100);
  }
  goto exit;
error:
  log_error(os.str()); os.str("");
exit:
  if(buf){
    free(buf);
  }
  if(f1.IsOpened()){f1.Close();}
  if(f2.IsOpened()){f2.Close();}
  log_message("FileSorter done.");
  signal_parent(ID_FILE_SORTER_WORKER_DONE);
  return NULL;
}



// file_sorter.cc ends here
