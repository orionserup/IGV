/**
 * @file IGV.cpp
 * @brief Contains Macro Behavior Implementation
 * @author Orion Serup
 * @bug None
 */ 
#include "IGV.hpp"

using namespace igv;
using namespace chrono;

#ifndef SIMULATION
IGV::IGV() : LCam(LANECAMPORT), OCam(OBJCAMPORT){}

#else

#endif

void IGV::Setup(){ // setup the threads 

  thread od(ObjDetection, this);
  thread ld(LaneDetection, this);
  thread sens(SensorLoop, this);
  thread lid(LidarLoop, this);
  thread gpsl(GPSLoop, this);

  ld.join();
  od.join();
  sens.join();
  lid.join();
  gpsl.join();

}

void IGV::Run(){

  // TODO: Implemetation

}

void igv::ObjDetection(IGV* igv){

  assert(igv);

  igv->OCam.Capture();
  igv->OD.DetectObjects(igv->OCam.GetImage());

}

void igv::LaneDetection(IGV* igv){

  assert(igv);

  igv->LCam.Capture();
  igv->LD.DetectLanes(igv->LCam.GetImage());

}

void igv::LidarLoop(IGV* igv) {
  
  assert(igv);

  igv->lidar.Probe();

}

void igv::GPSLoop(IGV* igv){
  
  assert(igv);

  igv->gps.Probe();

}

void igv::SensorLoop(IGV* igv){
  
  assert(igv);
  
  igv->us.Probe();

}
