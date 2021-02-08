#pragma once

#include "main.hpp"  // project defines

#ifndef SIMULATION
#include "CppLinuxSerial/SerialPort.hpp"
#include "CppLinuxSerial/Exception.hpp"

using namespace mn::CppLinuxSerial;
#endif
namespace igv {
class MotorController{

public:

  MotorController();  // by default the motor array comes from the HAL

  void ChangeDirection(DeltaDir deltadir, Speed speeddiff);  // changes the direction in motion
  void SetSpeed(Motor motor, Speed speed); // set the speed for one motor
  void SetSpeed(Speed speed);  // set the speed for both motors
  void Go(Distance dist, Speed speed, Direction dir); // go dist meters, at speed speed in dir direction
    
  Speed GetSpeed() const { return this->speed; }  // gets the current speed
  Direction GetDirection() const { return this->direction; } // gets the current direction
  bool isBusy() const { return busy; }

private:

  Direction direction;
  Speed speed;
  bool busy; 

  #ifndef SIMULATION

  SerialPort myport;

  #endif

};

}
