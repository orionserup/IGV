
#include "IGV.hpp"

using namespace igv;
using namespace chrono;

#ifndef SIMULATION
IGV::IGV():LCam(LANECAMPORT), OCam(OBJCAMPORT){}
#else

#endif

void IGV::Setup(){

  LCam.Capture();
  us.Probe();
  OCam.Capture();
  lidar.Probe();
  gps.Probe();
  LD.DetectLanes(LCam.GetImage());
  OD.DetectObjects(OCam.GetImage());

}


void IGV::Run(){

  thread ObjDet([&](){
    OCam.Capture();
    OD.DetectObjects(OCam.GetImage());
    this_thread::sleep_for(milliseconds(1000/ObjCamFPS));
  });

  thread LaneDet([&](){
    LCam.Capture();
    LD.DetectLanes(LCam.GetImage());
    this_thread::sleep_for(milliseconds(1000/LaneCamFPS));
  });
  
  bool finished = false;
  while(!finished){
    
    
    
  }
}




