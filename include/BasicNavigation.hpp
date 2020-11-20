
#include "hal.hpp"
#include <chrono>

using namespace std; 
using namespace chrono;

class MotorController{

public:

    MotorController();  // by default the motor array comes from the HAL

    void ChangeDirection(char dir){ this->direction = dir; }  // set the direction
    void SetSpeed(char speed) { this->speed = speed; }  // set the speed
    void Go(double dist, char speed, char dir); // go dist meters, at speed speed in dir direction

    void StopMotors();  // stops the motors

    char GetSpeed() const { return this->speed; }  // gets the current speed
    char GetDirection() const { return this->direction; } // gets the current direction

private:

    char direction, speed;
    HardwareInterface* hal;

    auto gettime(); 
    
    
};