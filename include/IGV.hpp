#pragma once

#include "ObjectDetection.hpp"
#include "BasicNavigation.hpp"
#include "LaneDetection.hpp"
#include "Camera.hpp"
#include "LIDAR.hpp"
#include "GPS.hpp"
#include "Ultrasonic.hpp"

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

void ODLoop(Camera& ocam, ObjDetector& od);
void LDLoop(Camera& lcam, LaneDetector& ld);
void GPSLoop(GPS& gps);
void LIDARLoop(LIDAR& lidar);
void USLoop(UltraSonic& us);

}

