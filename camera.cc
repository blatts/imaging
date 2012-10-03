// -*- mode: C++/lah -*-
// Time-stamp: "2012-10-03 13:17:49 sb"

/*
  file       camera.cc
  copyright  (c) Sebastian Blatt 2010, 2011, 2012

 */


#include "camera.hh"
#include "camera_worker.hh"
#include "andor_error_codes.hh"

#include <ATMCD32D.H>

#include <sstream>


Camera::Camera(CameraWorker* owner_)
  : owner(owner_),
    initialized(false),
    width(0),
    height(0),
    bitdepth(0),
    adchannels(0),
    amps(0),
    preamps(0),
    tmin(0),
    tmax(0),
    readouttime(0),
    using_kinetics(false),
    n_kinetics(0),
    rows_kinetics(0)
{
}

Camera::~Camera(){
}


bool Camera::Initialize() {
  bool rc = false;
  int ret = DRV_SUCCESS;
  std::ostringstream os;
  os << "Initialize DLL";
  owner->log_message(os.str()); os.str("");

  if((ret=::Initialize(ANDOR_DRIVER_DIRECTORY))!=DRV_SUCCESS){
    os << "Initialize()";
    goto error;
  }
  int t1=0,t2=0;
  float t[2] ={0,0};
  int s = 0, i=0, j=0, k=0, l=0;
  if(::GetDetector(&t1,&t2)!=DRV_SUCCESS){
    os << "GetDetector()";
    goto error;
  }
  width = t1;
  height = t2;
  os << "CCD dimensions : " << width << " x " << height;
  owner->log_message(os.str()); os.str("");

  t1=t2=0;
  if((ret=::GetNumberADChannels(&t1))!=DRV_SUCCESS){
    os << "GetNumberADChannels()";
    goto error;
  }
  adchannels = t1;
  os << "Number of AD Channels : " << adchannels;
  owner->log_message(os.str()); os.str("");

  t1=t2=0;
  if((ret=::GetNumberAmp(&t1))!=DRV_SUCCESS){
    os << "GetNumberAmp()";
    goto error;
  }
  amps = t1;
  os << "Number of Amplifiers : " << amps;
  owner->log_message(os.str()); os.str("");

  t1=t2=0;
  if((ret=::GetNumberPreAmpGains(&t1))!=DRV_SUCCESS){
    os << "GetNumberPreAmpGains()";
    goto error;
  }
  preamps = t1;
  os << "Preamp gain settings : (";
  for(i = 0; i<preamps; ++i){
    if((ret=::GetPreAmpGain(i,&t[0]))!=DRV_SUCCESS){
      os.str("");
      os << "GetPreAmpGain(" << i <<")";
      goto error;
    }
    os << t[0];
    if(i<preamps-1){
      os << ", ";
    }
  }
  t[0] = 0;
  os << ")";
  owner->log_message(os.str()); os.str("");

  if((ret=::SetPreAmpGain(preamps-1))!=DRV_SUCCESS){
    os << "SetPreAmpGain(" << preamps-1 << ")";
    goto error;
  }
  os << "Set preamp gain to max";
  owner->log_message(os.str()); os.str("");

  t1=t2=0;
  if((ret=::GetBitDepth(0,&t1))!=DRV_SUCCESS){
    os << "GetBitDepth(0)";
    goto error;
  }
  bitdepth = t1;
  os << "Bit depth : " << bitdepth;
  owner->log_message(os.str()); os.str("");

  // Set to maximum vertical speed
  if((ret=::GetNumberVSSpeeds(&s))!=DRV_SUCCESS){
    os << "GetNumberVSSpeeds()";
    goto error;
  }
  t[0] = 0;
  j=0;
  for(i=0; i<s; ++i){
    if((ret=::GetVSSpeed(i,&t[1]))!=DRV_SUCCESS){
      os << "GetVSSpeed()";
      goto error;
    }
    if(t[1]>t[0]){
      t[0] = t[1];
      j=i;
    }
  }
  if((ret=::SetVSSpeed(j))!=DRV_SUCCESS){
    os << "SetVSSpeed()";
    goto error;
  }
  os << "Vertical speed: " << t[0] << " us/px";
  owner->log_message(os.str()); os.str("");

  t[0] = t[1] = 0;
  i = j = s = 0;

  // set horizontal speed to max
  for(i=0; i<adchannels; ++i){
    if((ret=::GetNumberHSSpeeds(i,0,&s))!=DRV_SUCCESS){
      os << "GetNumberHSSpeeds()";
      goto error;
    }
    for(j=0; j<s; ++j){
      if((ret=::GetHSSpeed(i,0,j,&t[1]))!=DRV_SUCCESS){
        os << "GetHSSpeed()";
        goto error;
      }
      if(t[1]>t[0]){
        t[0] = t[1];
        k = j;
        l = i;
      }
    }
  }
  if((ret=::SetADChannel(l))!=DRV_SUCCESS){
    os << "SetADChannel()";
    goto error;
  }
  os << "AD Channel: " << l;
  owner->log_message(os.str()); os.str("");
  if((ret=::SetHSSpeed(0,k))!=DRV_SUCCESS){
    os << "SetHSSpeed()";
    goto error;
  }
  os << "Horizontal speed: " << t[0] << " MHz";
  owner->log_message(os.str()); os.str("");


  t1=t2=0;
  if((ret=::GetTemperatureRange(&t1,&t2))!=DRV_SUCCESS){
    os << "GetTemperatureRange()";
    goto error;
  }
  tmin = t1;
  tmax = t2;
  os << "Temperature range: [" << t1 << "," << t2 << "]";
  owner->log_message(os.str()); os.str("");

  if((ret=::SetTemperature(ANDOR_CAMERA_TEMPERATURE))!=DRV_SUCCESS){
    os << "SetTemperature(" << ANDOR_CAMERA_TEMPERATURE << ")";
    goto error;
  }
  os << "Temperature set to " << ANDOR_CAMERA_TEMPERATURE << " C";
  owner->log_message(os.str()); os.str("");

  if((ret=::CoolerON())!=DRV_SUCCESS){
    os << "CoolerON()";
    goto error;
  }
  owner->log_message("Cooler turned on"); os.clear();
  owner->log_message("Initialization done.");
  rc = true;
  initialized = true;
  goto exit;
error:
  os << " failed with " << andor_strerr(ret);
  owner->log_error(os.str()); os.str("");
  Shutdown();
exit:
  return rc;
}

int Camera::GetTemperature() {
  int t = 666;
  if(!initialized){
    return t;
  }
  unsigned int rc = ::GetTemperature(&t);
  if(rc == DRV_TEMP_STABILIZED ||
     rc == DRV_TEMP_NOT_REACHED ||
     rc == DRV_TEMP_DRIFT ||
     rc == DRV_TEMP_NOT_STABILIZED)
  {
  }
  else{
    std::ostringstream os;
    os << "GetTemperature failed with " << andor_strerr(rc);
    owner->log_message(os.str()); os.str();
  }
  return t;
}

bool Camera::SetupExperiment(float exposure_time,
                             shutter_mode_t shutter_mode,
                             bool internal_trigger,
                             bool kinetics_mode,
                             unsigned int number_kinetics
                            )
{
  bool ret = false;
  if(!initialized){
    return ret;
  }
  int rc = DRV_SUCCESS;
  float t[3] ={0,0,0};
  int i=0;
  std::ostringstream os;

  // Use either fast kinetics mode or single image
  if((rc=::SetAcquisitionMode(kinetics_mode?4:1))!=DRV_SUCCESS){
    os << "SetAcquisitionMode()";
    goto error;
  }

  // Always read full image
  if((rc=::SetReadMode(4))!=DRV_SUCCESS){
    os << "SetReadMode()";
    goto error;
  }

  // Set exposure time
  if((rc=::SetExposureTime(exposure_time))!=DRV_SUCCESS){
    os << "SetExposureTime()";
    goto error;
  }

  // Setup fast kinetics mode if requested
  using_kinetics = kinetics_mode;
  if(using_kinetics){
    n_kinetics = number_kinetics;
    rows_kinetics = height/n_kinetics;
    if((rc=::SetFastKineticsEx(rows_kinetics,n_kinetics,exposure_time,4,
                               ANDOR_HBIN,ANDOR_VBIN,(n_kinetics-1)*rows_kinetics
                              ))!=DRV_SUCCESS)
    {
      os << "SetFastKinetics()";
      goto error;
    }
  }

  // Query final timing from camera
  //   GetReadOutTime() does not exist for iKon model!
  if((rc=::GetAcquisitionTimings(&t[0],&t[1],&t[2]))!=DRV_SUCCESS){
    os << "GetAcquisitionTimings()";
    goto error;
  }
  os << "Acquisition timings : exposure:" << t[0] << ", accumulate:"
     << t[1] << ", kinetic: " << t[2];
  owner->log_message(os.str()); os.str("");


  // Setup Shutter
  if (shutter_mode==AUTOMATIC)         {i = 0;}
  else if (shutter_mode==ALWAYS_OPEN)  {i = 1;}
  else if (shutter_mode==ALWAYS_CLOSED){i = 2;}
  else                                 {i = ANDOR_SHUTTER_MODE;}
  if((rc=::SetShutter(ANDOR_SHUTTER_TTL,i,
                      ANDOR_SHUTTER_CLOSETIME,
                      ANDOR_SHUTTER_OPENTIME))!=DRV_SUCCESS)
  {
    os << "SetShutter()";
    goto error;
  }


  // Setup trigger polarity is such that TTL high triggers
  i = internal_trigger?0:1;
  if((rc=::SetTriggerMode(i))!=DRV_SUCCESS){
    os << "SetTriggerMode()";
    goto error;
  }

  // Setup ROI for readout and binning, always use full chip here
  if((rc=::SetImage(ANDOR_HBIN,ANDOR_VBIN,1,width,1,height))!=DRV_SUCCESS){
    os << "SetImage()";
    goto error;
  }

/*
  if((rc=::SetNumberAccumulations(1))!=DRV_SUCCESS){
     os << "SetNumberAccumulations()";
     goto error;
  }
  if((rc=::SetNumberKinetics(1))!=DRV_SUCCESS){
    os << "SetNumberKinetics()";
    goto error;
  }
  if((rc=::SetAccumulationCycleTime(1.0f))!=DRV_SUCCESS){
    os << "SetAccumulationCycleTime()";
    goto error;
  }
  if((rc=::SetKineticCycleTime(1.0f))!=DRV_SUCCESS){
    os << "SetKineticCycleTime()";
    goto error;
  }
*/

  owner->log_message("Experiment set up successfully.");
  ret = true;
  goto exit;
error:
  os << " failed with " << andor_strerr(rc);
  owner->log_error(os.str()); os.str("");
exit:
  return ret;
}

bool Camera::StartExperiment() {
  if(!initialized){
    return false;
  }
  unsigned int rc = DRV_SUCCESS;
  if((rc=::StartAcquisition())!=DRV_SUCCESS){
    ::AbortAcquisition();
    std::ostringstream os;
    os << "StartAcquisition() failed with " << andor_strerr(rc);
    owner->log_error(os.str()); os.str("");
    return false;
  }
  return true;
}

int Camera::GetStatus(){
  if(!initialized){
    return -1;
  }
  unsigned int rc = DRV_SUCCESS;
  int status=0;
  std::ostringstream os;
  if((rc=::GetStatus(&status))!=DRV_SUCCESS){
    os << "GetStatus() failed with " << andor_strerr(rc);
    owner->log_error(os.str()); os.str("");
    return 0;
  }
  if(status == DRV_TEMPCYCLE ||
     status == DRV_ACCUM_TIME_NOT_MET||
     status == DRV_KINETIC_TIME_NOT_MET||
     status == DRV_ERROR_ACK ||
     status == DRV_ACQ_BUFFER ||
     status == DRV_SPOOLERROR)
  {
    os << "GetStatus() returned " << andor_strerr(status);
    owner->log_error(os.str()); os.str("");
    return 1;
  }
  if(status == DRV_ACQUIRING){
    return 2;
  }
  if(status == DRV_IDLE){
    return 3;
  }
  // should not get here!
  return 4;
}

// Assume that raw_image_data is allocated with dimensions given by
// width*height. Also assume that raw_image_data is already mutex
// protected by caller.
bool Camera::DownloadImage(long** raw_image_data){
  if(!initialized){
    return false;
  }
  unsigned int rc = DRV_SUCCESS;
  bool ret = false;
  std::ostringstream os;
  at_32 t1=0,t2=0;
  long n1=0,n2=0;
  unsigned int n=0;
  if((rc=::GetNumberAvailableImages(&t1,&t2))!=DRV_SUCCESS){
    os << "GetNumberAvailableImages()";
    goto error;
  }
  //os << "Available image range for download [" << t1 << ", " << t2 << "]";
  //owner->log_message(os.str()); os.str("");

  // if((rc=::GetAcquiredData(*raw_image_data,GetImageArea()))
//      !=DRV_SUCCESS)
//   {
//     os << "GetAcquiredData(" << raw_image_data
//        << ", " << GetImageArea() << ")";
//     goto error;
//   }
  if(t1==1 && t2==1){
    n = GetImageArea();
  }
  else{
    n = (t2-t1+1)*rows_kinetics*width;
  }
  n1 = t1, n2 = t2;
  t1 = t2 = 0;
  if((rc=::GetImages(n1,n2,*raw_image_data,n,&t1,&t2))!=DRV_SUCCESS){
    os << "GetImages()";
    goto error;
  }

  ret = true;
  goto exit;
error:
  os << " failed with " << andor_strerr(rc);
  owner->log_error(os.str()); os.str("");
exit:
  return ret;
}

bool Camera::SaveLastImageTIFF(const std::string& path){
  if(!initialized){
    return false;
  }
  unsigned int rc=DRV_SUCCESS;
  size_t n = (using_kinetics)?n_kinetics:1;
  std::ostringstream os;
  for(size_t i=0; i<n; ++i){
    os.str("");
    os << path << "_" << i;
    if((rc=::SaveAsTiffEx((char*)os.str().c_str(),ANDOR_PALETTE,i+1,1,1))!=DRV_SUCCESS){
      std::ostringstream os;
      os << "SaveAsTiffEx() failed with " << andor_strerr(rc);
      owner->log_error(os.str()); os.str("");
      return false;
    }
  }
  return true;
}


bool Camera::AbortExperiment() {
  bool ret = false;
  if(!initialized){
    return ret;
  }
  unsigned int rc=DRV_SUCCESS;
  int t=0;
  std::ostringstream os;
  if((rc=::GetStatus(&t))!=DRV_SUCCESS){
    os << "GetStatus()";
    goto error;
  }
  if(t != DRV_IDLE){
    if((rc=::AbortAcquisition())!=DRV_SUCCESS){
      os << "AbortAcquisition()";
      goto error;
    }
  }
  ret = true;
  goto exit;
error:
  os << " failed with " << andor_strerr(rc);
  owner->log_error(os.str()); os.str("");
exit:
  return ret;
}


void Camera::Shutdown(){
  if(!initialized){
    return;
  }
  unsigned int rc = DRV_SUCCESS;
  std::ostringstream os;

  if((rc=::FreeInternalMemory())!=DRV_SUCCESS){
    os << "FreeInternalMemory() failed with " << andor_strerr(rc);
    owner->log_error(os.str()); os.str("");
  }

  if((rc=::CoolerOFF())!=DRV_SUCCESS){
    os << "CoolerOFF() failed with " << andor_strerr(rc);
    owner->log_error(os.str()); os.str("");
  }
  else{
    owner->log_message("Cooler turned off");
  }
  if((rc=::ShutDown())!=DRV_SUCCESS){
    os << "ShutDown() failed with " << andor_strerr(rc);
    owner->log_error(os.str()); os.str("");
  }
  else{
    owner->log_message("Camera shut down");
  }
}

wxString Camera::GetVersionInformation(){
  if(!initialized){
    return "Driver not initialized";
  }
  char buf[256];
  memset(buf,0,sizeof(buf));
  std::string rc = "";
  if(GetVersionInfo(AT_DeviceDriverVersion,buf,sizeof(buf)) == DRV_SUCCESS){
    rc += "Driver version " + std::string(buf);
  }
  if(GetVersionInfo(AT_SDKVersion,buf,sizeof(buf)) == DRV_SUCCESS){
    rc += " SDK version " + std::string(buf);
  }
  return rc;
}



// camera.cc ends here
