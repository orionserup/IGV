
#include "IGV.hpp"

using namespace igv;
using namespace chrono;


#ifndef SIMULATION
IGV::IGV():
  LCam(LANECAMPORT), OCam(OBJCAMPORT){}

#else

#endif

void IGV::Setup(){ // setup the threads

  ObjDetection = thread([&](){
    
    OCam.Capture();
    OD.DetectObjects(OCam.GetImage());
    this_thread::sleep_for(milliseconds(1000/ObjCamFPS));

  });

  LaneDetection = thread([&](){
    
    LCam.Capture();
    LD.DetectLanes(LCam.GetImage());
    this_thread::sleep_for(milliseconds(1000/LaneCamFPS));

  });

  LidarLoop = thread([&](){
    
    lidar.Probe();
    this_thread::sleep_for(milliseconds(1000/LIDARFPS));
    
  });

  GPSLoop = thread([&](){
  
    this_thread::yield();

    gps.Probe();
    this_thread::sleep_for(milliseconds((uint64_t)(1000/GPSFPS)));

  });

  SensorLoop = thread([&](){  

    this_thread::yield();
      
    us.Probe();
    this_thread::sleep_for(milliseconds(1000/ULTRAFPS));
  
  });


}

void IGV::Run(){

  // TODO: Implemetation


  

}





