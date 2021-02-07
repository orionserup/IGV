#pragma once

#include "Defines.hpp"
#include "ObjectDetection.hpp"
#include "BasicNavigation.hpp"
#include "LaneDetection.hpp"
#include "Camera.hpp"
#include "LIDAR.hpp"
#include "GPS.hpp"
#include "Ultrasonic.hpp"

#include <thread>  // multithreading

namespace igv{

class IGV{

public:

  IGV();
  
  void Setup();
  void Run();

private:

  MotorController MC;
  ObjDetector OD;
  LaneDetector LD;
  Camera LCam, OCam;
  LIDAR lidar;
  GPS gps;
  UltraSonic us;

};

void ODLoop();
void LDLoop();
void GPSLoop();
void LIDARLoop();
void NavLoop();

}

