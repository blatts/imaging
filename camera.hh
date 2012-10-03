// -*- mode: C++/lah -*-
// Time-stamp: "2012-10-03 10:55:36 sb"

/*
  file       camera.hh
  copyright  (c) Sebastian Blatt 2010, 2011, 2012

 */


#ifndef CAMERA_HH
#define CAMERA_HH


#include <wx/wx.h>
#include <string>

#include "camera_control.hh"

class CameraWorker;
class Camera{
  private:
    CameraWorker* owner;
    bool initialized;

    int width;
    int height;
    int bitdepth;
    int adchannels;
    int amps;
    int preamps;
    int tmin;
    int tmax;
    float readouttime;
    bool using_kinetics;
    unsigned int n_kinetics;
    unsigned int rows_kinetics;

  public:
    Camera(CameraWorker* owner_);
    virtual ~Camera();

    bool Initialize();
    int GetTemperature();
    bool SetupExperiment(float exposure_time,
                         shutter_mode_t shutter_mode,
                         bool internal_trigger,
                         bool kinetics_mode,
                         unsigned int number_kinetics
                        );
    bool StartExperiment();
    int GetStatus();
    bool DownloadImage(long** raw_image_data);
    bool SaveLastImageTIFF(const std::string& path);
    //bool SaveImageTIFF(const std::string& path, long** raw_image_data);

    bool AbortExperiment();
    void Shutdown();
    wxString GetVersionInformation();

    const int GetImageWidth() const {return width;}
    const int GetImageHeight() const {return height;}
    const int GetImageArea() const {return width*height;}
    const int GetImageBytes() const {return width*height*bitdepth/2;}
};


#endif // CAMERA_HH

// camera.hh ends here
