// -*- mode: C++/lah -*-
// Time-stamp: "2010-01-25 20:15:20 srgang"

/*
  file       file_sorter.hh
  copyright  (c) Sebastian Blatt 2010

 */


#ifndef FILE_SORTER_HH
#define FILE_SORTER_HH

#include <wx/wx.h>
#include <wx/thread.h>
#include <queue>
#include <string>

typedef std::queue<std::string> message_queue_t;
class FileSorterWorker : public wxThread{
  private:
    wxFrame* parent;
    message_queue_t* message_queue;
    wxMutex* message_queue_mutex;
    message_queue_t* command_queue;
    wxMutex* command_queue_mutex;
    std::string target_directory;

    FileSorterWorker(FileSorterWorker&) {}
    void signal_parent(int id);
  public:
    FileSorterWorker(wxFrame* parent_,
                     message_queue_t* message_queue_,
                     wxMutex* message_queue_mutex_,
                     message_queue_t* command_queue_,
                     wxMutex* command_queue_mutex_,
                     const std::string target_directory_
                    );
    ~FileSorterWorker();

    virtual void* Entry();
    void log_message(const std::string& msg);
    void log_error(const std::string& msg);

};

DECLARE_EVENT_TYPE(wxEVT_FILE_SORTER,-1)

#endif // FILE_SORTER_HH

// file_sorter.hh ends here
