
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
  
    while(1){

    gps.Probe();
    this_thread::sleep_for(milliseconds((uint64_t)(1000/GPSFPS)));
    
    }
  });

  UltraLoop = thread([&](){  
    
    while(1){
      
    us.Probe();
    this_thread::sleep_for(milliseconds(1000/ULTRAFPS));
  
    }
  });

  UltraLoop.yield();  // put the ultrasonic on the buttom of the stack
  GPSLoop.yield();   // same for the gps

}

void IGV::Run(){

  UltraLoop.yield()  // put the ultrasonic on the buttom of the stack
  GPSLoop.yield()

  // TODO: Implemetation


  

}





