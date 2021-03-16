/**
 * @file IGV.hpp
 * @brief Holds the IGV class with all sensors and such
 * @author Orion Serup
 * @bug None
 */

#pragma once

#include "ObjectDetection.hpp"
#include "BasicNavigation.hpp"
#include "LaneDetection.hpp"
#include "Camera.hpp"
#include "LIDAR.hpp"
#include "GPS.hpp"
#include "Sensors.hpp"

/**
* @brief namespace for this project
*/
namespace igv{

/**
* @brief The Complete Vehicle Class 
*/
class IGV{

public:

  /**
  * @brief Constructs an IGV object
  */
  IGV();
  
  /**
  * @brief Starts all Sensors and Probes them all
  */
  void Setup();

  /**
  * @brief Starts running autonomously
  */
  void Run();
  
  friend void ObjDetection(IGV* igv);
  friend void LaneDetection(IGV* igv);
  friend void LidarLoop(IGV* igv);
  friend void GPSLoop(IGV* igv);
  friend void SensorLoop(IGV* igv);

private:

  MotorController MC;
  ObjDetector OD;
  LaneDetector LD;
  Camera LCam, OCam;
  LIDAR lidar;
  GPS gps;
  UltraSonic us;

};

void ObjDetection(IGV* igv);
void LaneDetection(IGV* igv);
void LidarLoop(IGV* igv);
void GPSLoop(IGV* igv);
void SensorLoop(IGV* igv);

}

