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

  setNumThreads(8);

  thread od([&](){ OD.DetectObjects(OCam.GetImage(), LCam.GetImage()); });
  thread ld([&](){ LD.DetectLanes(LCam.GetImage()); });

  ld.join();
  od.join();


}

void IGV::Run(){

  if(LD.GetLanes().size()) // if we detected any lanes
  {

    Speed speed = MC.GetSpeed();
    Direction deltadir;
    double orientation = 0.0f;

    for(Lane lane: LD.GetLanes()) // add all of the lane slopes to see how we are oriented
      orientation += lane.slope;

    // if the lanes appear skewed clockwise we need to go right to correct ourselves
    // and the inverse for the skew counter clockwise

    // we have to come up with a correction factor that goes from 0 to 1 as orientation goes from 0 -> inf
    // it also has to go from 0 to -1 as orientation does from 0 -> -inf, thats arctan/(pi / 2) as it goes to pi/2
    double correctionfactor = atan(orientation) / M_PI_2;

    // we now set the change indirection to be a 90 degree turn multiplied by the correction factor
    deltadir = 64.0f * correctionfactor; // works for positive and negative orientation

    // Now we need to change the actual direction, the worse we are, the faster we need to turn
    MC.ChangeDirection(deltadir, correctionfactor * speed); 

  }
  
}
