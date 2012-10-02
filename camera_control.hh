// -*- mode: C++/lah -*-
// Time-stamp: "2012-10-02 15:05:06 sb"

/*
  file       camera_control.hh
  copyright  (c) Sebastian Blatt 2010, 2011, 2012
  url        http://wiki.havens.de

 */


#ifndef CAMERA_CONTROL_HH
#define CAMERA_CONTROL_HH

#include <string>


#define ANDOR_CAMERA_TEMPERATURE -100
#define ANDOR_DIRECTORY "c:\\Program Files\\Andor SOLIS"
#define ANDOR_DRIVER_DIRECTORY ANDOR_DIRECTORY ## "\\Drivers"
#define ANDOR_PALETTE ANDOR_DIRECTORY ## "\\GLOW.PAL"

// Acquisition mode
//   1 : single scan
//   2 : accumulate
//   3 : kinetics
//   4 : fast kinetics
//   5 : run until abort
#define ANDOR_ACQUISITION_MODE 1

// Read mode
//   0 : full vertical binning (integration)
//   4 : full image
#define ANDOR_READ_MODE 4

// Shutter mode:
//   0 : auto
//   1 : always open
//   2 : always closed
#define ANDOR_SHUTTER_MODE 0

// Shutter polarity
//   0 : TTL low to open
//   1 : TTL high to open
#define ANDOR_SHUTTER_TTL 1

// Shutter preopen and close times in ms
#define ANDOR_SHUTTER_OPENTIME 20
#define ANDOR_SHUTTER_CLOSETIME 20

// Trigger mode
//   0 : internal
//   1 : external
//   2 : external start (fast kinetics only)
#define ANDOR_TRIGGER_MODE 1

// horizontal and vertical binning in px
#define ANDOR_HBIN 1
#define ANDOR_VBIN 1

// exposure time in s (float)
#define ANDOR_EXPOSURE_TIME 0.001f


#define IMAGE_SPOOL_PATH "e:\\image_spool"
#define IMAGE_NAME_FORMAT "%y%m%d-%H%M%S"

typedef enum {AUTOMATIC,ALWAYS_OPEN,ALWAYS_CLOSED} shutter_mode_t;


class CameraExperimentControl{
  public:
    float exposure_time;
    shutter_mode_t shutter_mode;
    bool internal_trigger;
    bool kinetics_mode;
    bool process_kinetics;
    unsigned int number_kinetics;
    bool save_images;
    std::string image_spool_path;

    CameraExperimentControl()
      : exposure_time(0.1f),
        shutter_mode(ALWAYS_OPEN),
        internal_trigger(true),
        kinetics_mode(false),
        process_kinetics(false),
        number_kinetics(3),
        save_images(false),
        image_spool_path(IMAGE_SPOOL_PATH)
    {}
};


#endif // CAMERA_CONTROL_HH

// camera_control.hh ends here
