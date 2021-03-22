/**
 * @file IGV.hpp
 * @brief Holds the IGV class with all sensors and such
 * @author Orion Serup
 * @bug None
 */

/** 
 * @mainpage UCI IGV 2020 - 2021
 * @authors Orion Serup (Lead Dev)
 * @authors Gabriel Enciso (Team Lead)
 * 
 * This Project is the UCI Intelligent Vehicle Project
 * for the Intelligent Vehicle Competition.
 * 
 * The Goal of this project is to create a fully autonomous vehicle
 * that detectes and stay within lanes, detects and avoids objects; it also uses LIDAR,
 * GPS, and other Sensors to be aware of its surroundings.
 * 
 * The Project is in partnership with Northrup Grummon.
 * 
 * @ref Contributions
 * 
 */

/** 
 * @page Contributions
 * @details Thanks to the following GitHub Users for creating code that is used in this Project.
 * 
 * For the Serial Library: gbmhunter.
 * 
 * For the JetsonGPIO Library: pjueon.
 * 
 * For the GPS Library: mikalhart.
 * 
 * For OpenCV: The OpenCV team (opencv).
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

  /**
   * @brief 
   * 
   *
   */
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

