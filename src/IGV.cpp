
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
    
    while(1){
      
    OCam.Capture();
    OD.DetectObjects(OCam.GetImage());
    this_thread::sleep_for(milliseconds(1000/ObjCamFPS));
  
    }
  });

  LaneDetection = thread([&](){
    
    while(1){
    
    LCam.Capture();
    LD.DetectLanes(LCam.GetImage());
    this_thread::sleep_for(milliseconds(1000/LaneCamFPS));
    
    }
  });

  LidarLoop = thread([&](){
    
    while(1){
    
    lidar.Probe();
    this_thread::sleep_for(milliseconds(1000/LIDARFPS));
    
    }
  });

  GPSLoop = thread([&](){
  
    this_thread::yield();
    
    while(1){

    gps.Probe();
    this_thread::sleep_for(milliseconds((uint64_t)(1000/GPSFPS)));
    
    }
  });

  UltraLoop = thread([&](){  

    this_thread::yield();
    
    while(1){
      
    us.Probe();
    this_thread::sleep_for(milliseconds(1000/ULTRAFPS));
  
    }
  });


}

void IGV::Run(){

  // TODO: Implemetation


  

}





