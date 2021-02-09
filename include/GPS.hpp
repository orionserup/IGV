#pragma once

#include "main.hpp"
#ifndef SIMULATION
#include "CppLinuxSerial/Exception.hpp"
#include "CppLinuxSerial/SerialPort.hpp"

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
  long double GetLatitude() { return position.Latitude; }
  long double GetLongitude() { return position.Longitude; }
  GPSData& GetGPSData() { return position; }
  bool isBusy(){ return busy; }

private:

  GPSData position;
  uint8_t data[255];
  bool busy;

  #ifndef SIMULATION

  SerialPort myport;

  #endif

};


