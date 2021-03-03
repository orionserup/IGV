#pragma once

#include "main.hpp"

#include "TinyGPS++.h"  // GPS utilities

#ifndef SIMULATION
#include "CppLinuxSerial/Exception.hpp"
#include "CppLinuxSerial/SerialPort.hpp"

#include <linux/i2c-dev.h>

using namespace mn::CppLinuxSerial;
#endif

namespace igv{

class GPS{
  
public:

  GPS();

  Direction GetBearingTo(double lat, double lon);
  double GetDistanceTo(double lat, double lon);

  void Probe();
  double GetLatitude() { return CurrLat; }
  double GetLongitude() { return CurrLong; }
  bool isBusy(){ return busy; }
  
private:

  TinyGPSPlus gps;
  double CurrLat, CurrLong;
  bool busy;

  #ifndef SIMULATION

  SerialPort myport;

  #endif

};

}


