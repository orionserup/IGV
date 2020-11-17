
#include "hal.hpp"

class MotorController{

public:

    MotorController(Motor* motors); // if there is already a motor array 
    MotorController();  // by default the motor array comes from the HAL

    void SetDirection(char dir){ this->direction = dir; }  // set the direction
    void SetSpeed(char speed) { this->speed = speed; }  // set the speed
    void Go(double dist, char speed, char dir); // go dist meters, at speed speed in dir direction

    void UpdateMotors(); // send the current parameters to the motors
    void StopMotors();  // stops the motors

    char GetSpeed() const { return this->speed; }  // gets the current speed
    char GetDirection() const { return this->direction; } // gets the current direction

private:

    char direction, speed;
    HardwareInterface* hal;
    
};