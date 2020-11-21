#include "BasicNavigation.hpp"

MotorController::MotorController(HardwareInterface* hal){

    direction = 0;
    speed = 0;
    this->hal = &hal; 

}

void MotorController::ChangeDirection(char dir, char speeddiff){

    if(busy) return;  // if doing something else exit

    char currspeed = hal->motors[LEFT].GetSpeed(); // get the current motor speed
    double ohmega;  // angular velocity in terms of change in direction per second using dir = [-127, 127]
    milliseconds waittime; // wait time to travel dir angular distance

    direction = (direction + dir) & 127;  // update the direction so that its mag is not above 127

    if( (int(speeddiff) + currspeed) > 127 ) speeddiff = 127 - currspeed;  // correct the speed diff if too high or low
    if( (int(currspeed) - speeddiff) < -127 ) speeddiff = currspeed - 127;

    ohmega = (speeddiff / (M_PI *  WHEELBASE * 508.0f));  // get tangential speed and convert it to angular

    waittime = milliseconds(dir > 0 ? uint64_t(1000*dir/ohmega): uint64_t(1000* ~(dir - 1)/ohmega));

    busy = true;
    
    hal->motors[LEFT].SetSpeed( (dir > 0) ? currspeed - speeddiff: currspeed + speeddiff);
    hal->motors[RIGHT].SetSpeed( (dir > 0) ? currspeed + speeddiff: currspeed - speeddiff);

    this_thread::sleep_for(waittime);

    hal->motors[LEFT].SetSpeed(currspeed);
    hal->motors[RIGHT].SetSpeed(currspeed);

    busy = false;

}
