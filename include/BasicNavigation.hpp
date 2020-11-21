#pragma once

#include "hal.hpp"
#include <chrono>
#include <thread>
#include <math.h>

#define LEFT 0
#define RIGHT 1
#define CENTER 0

using namespace std; 
using namespace chrono;

class MotorController{

public:

    MotorController(HardwareInterface& hal);  // by default the motor array comes from the HAL

    void ChangeDirection(char dir, char speed);
    void SetSpeed(char speed) { this->speed = speed; }  // set the speed
    void Go(double dist, char speed, char dir); // go dist meters, at speed speed in dir direction

    void StopMotors();  // stops the motors

    char GetSpeed() const { return this->speed; }  // gets the current speed
    char GetDirection() const { return this->direction; } // gets the current direction

private:

    char direction, speed;
    HardwareInterface& hal;
    bool busy; 
    
};