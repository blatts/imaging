// -*- mode: C++/lah -*-
// Time-stamp: "2010-01-29 10:56:09 srgang"

/*
  file       camera_worker.hh
  copyright  (c) Sebastian Blatt 2010

 */


#ifndef CAMERA_WORKER_HH
#define CAMERA_WORKER_HH


#define SHUTDOWN_DELAY 5

#include <wx/wx.h>
#include <wx/thread.h>
#include <queue>
#include <string>

typedef std::queue<std::string> message_queue_t;
class Camera;
class CameraExperimentControl;
class CameraWorker : public wxThread {
  private:
    wxFrame* parent;
    message_queue_t* message_queue;
    message_queue_t* command_queue;
    wxMutex* message_queue_mutex;
    wxMutex* command_queue_mutex;
    long** raw_picture_data;
    wxMutex* raw_picture_data_mutex;
    Camera* camera;
    wxString image_spool_path;
    CameraExperimentControl* experiment_control;
    wxMutex* experiment_control_mutex;
    wxString experiment_timestamp;

    bool save_images;
    bool using_kinetics;
    size_t n_kinetics;

    CameraWorker(CameraWorker&){}
    void signal_parent(int id, const std::string& msg="");

    std::string get_timestamp_file();
    std::string get_timestamp_path(const std::string& timestamp_file);

  public:
    CameraWorker(wxFrame* parent_,
                 message_queue_t* message_queue_,
                 message_queue_t* command_queue_,
                 wxMutex* message_queue_mutex_,
                 wxMutex* command_queue_mutex_,
                 long** raw_picture_data,
                 wxMutex* raw_picture_data_mutex_,
                 CameraExperimentControl* experiment_control_,
                 wxMutex* experiment_control_mutex_
                );
    ~CameraWorker();

    virtual void* Entry();

    void log_message(const std::string& msg);
    void log_error(const std::string& msg);

    void signal_experiment_begin();
    void signal_experiment_end();
    void signal_image_ready(size_t n_images, const std::string& locator="");

    bool check_for_interrupt();
    void clear_command_queue();
    bool update_camera_control(bool setup_experiment);
    void update_experiment_timestamp();

};

DECLARE_EVENT_TYPE(wxEVT_CAMERA_DATA,-1)


#endif // CAMERA_WORKER_HH

// camera_worker.hh ends here
