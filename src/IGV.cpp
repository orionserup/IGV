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

  OCam.Capture();
  LCam.Capture();
  gps.Probe();
  lidar.Probe();

  thread od([&](){ OD.DetectObjects(OCam.GetImage()); });
  thread ld([&](){ LD.DetectLanes(LCam.GetImage()); });

  ld.join();
  od.join();

}

void IGV::Run(){

  // TODO: Implemetation

  

}
