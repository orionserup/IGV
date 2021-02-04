#pragma once

#include "hal.hpp"
#include <chrono> // wait funtionality
#include <thread>

#define WHEELBASE 31.0f

using namespace chrono;

namespace igv {

class MotorController{

public:

  MotorController(HardwareInterface& hal);  // by default the motor array comes from the HAL

  void ChangeDirection(DeltaDir deltadir, Speed speeddiff);  // changes the direction in motion
  void SetSpeed(Speed speed); // set the speed
  void Go(Distance dist, Speed speed, Direction dir); // go dist meters, at speed speed in dir direction
    
  Speed GetSpeed() const { return this->speed; }  // gets the current speed
  Direction GetDirection() const { return this->direction; } // gets the current direction
  bool isBusy() const { return busy; }

private:

  Direction direction;
  Speed speed;
  HardwareInterface& hal;
  bool busy; 
    
};

}
