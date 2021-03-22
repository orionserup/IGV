/**
 * @file GPS.hpp
 * @brief Holds the Prototypes for the GPS Functionality
 * @author Orion Serup
 * @bug None
 */

#pragma once

#include "main.hpp"

#include "TinyGPS++.h"  // GPS utilities

#ifndef SIMULATION
#include "CppLinuxSerial/Exception.hpp"
#include "CppLinuxSerial/SerialPort.hpp"

#include <linux/i2c-dev.h>

using namespace mn::CppLinuxSerial;
#endif

/**
* @namespace igv
* @brief namespace for this project
*/
namespace igv{

/**
* @class GPS
* @brief Container Class for a gps module, abstracts from hardware
*/
class GPS{
  
public:

  /**
  * @fn GPS()
  * @brief Constructs a GPS Object
  */
  GPS();

  /** 
  * @fn Direction GetBearingTo(double lat, double lon)
  * @brief Gets the direction to that lattitude and longitude
  * @param lat Lattitude of coordinate to Get Bearing to
  * @param lon Longitude of coordinate to Get Bearing to
  * @returns Direction to that point
  */
  Direction GetBearingTo(double lat, double lon);
  
  /**
  * @fn Distance GetDistanceTo(double lat, double long)
  * @brief Gets the Distance from current location to a fixed lattitude and longitude
  * @param lat Lattitude of coordinate to Get Distance to
  * @param lon Longitude of coordinate to Get Distance to
  * @returns Distance to the Point
  */ 
  Distance GetDistanceTo(double lat, double lon);

  /**
  * @fn void Probe()
  * @brief Probes the Satellite for GPS data and records Lat and Long
  */
  void Probe();

  /**
  * @fn double GetLatitude()
  * @brief Returns the Current Latitude
  * @returns Current Latitude
  */
  double GetLatitude() { return CurrLat; }
  
  /**
  * @fn double GetLongitude()
  * @brief Returns the Current Longitude
  * @returns Current Longitude
  */
  double GetLongitude() { return CurrLong; }
  
  /**
  * @fn bool isBusy()
  * @brief Checks if the GPS is busy probing
  * @returns bool: If the GPS is busy with an operation
  */
  bool isBusy() const { return busy; }
  
private:

  TinyGPSPlus gps; 
  double CurrLat, CurrLong;
  bool busy;

  #ifndef SIMULATION

  SerialPort myport;

  #endif

};

}


