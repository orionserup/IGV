#pragma once

#include "main.hpp"

#include "TinyGPS++.h"  // GPS utilities

#ifndef SIMULATION
#include "CppLinuxSerial/Exception.hpp"
#include "CppLinuxSerial/SerialPort.hpp"

#include <linux/i2c-dev.h>

using namespace mn::CppLinuxSerial;
#endif

using namespace igv;

struct GPSData{

  long double Latitude, Longitude;

};

class GPS{
    
public:

  GPS();

  void Probe();
  double GetLatitude() { return gps.location.lat(); }
  double GetLongitude() { return gps.location.lng(); }
  Direction GetDirection();
  bool isBusy(){ return busy; }

private:

  TinyGPSPlus gps;
  uint8_t data[255];
  bool busy;

  #ifndef SIMULATION

  SerialPort myport;

  #endif

};


