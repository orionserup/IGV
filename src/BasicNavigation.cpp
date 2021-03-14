#include "BasicNavigation.hpp"

using namespace igv;
using namespace std;
using namespace chrono;


void MotorController::SetSpeed(Speed speed){

  SetSpeed(LEFT, speed);
  SetSpeed(RIGHT, speed);

}

#ifndef SIMULATION

MotorController::MotorController() : myport(MCPORT, B9600){
  busy = false;
  speed = 0;
  direction = 0;
}

void MotorController::SetSpeed(Motor motor, Speed speed) {

  uint8_t command = 0;
  string msg = " ";
  uint8_t magnitude = abs(speed) >> 1;
  
  if (motor == LEFT)
    command = speed < 0 ? 63 - magnitude : 64 + magnitude;
  
  else
    command = speed < 0 ? 191 - magnitude : 192 + magnitude;
  
  command = (!command)? 1: (command == 0xff)? 254: command;
  
  msg[0] = command;
  
  this->myport.Write(msg);

}


void MotorController::ChangeDirection(DeltaDir deltadir, Speed speeddiff) {

  if (busy || !deltadir || !speeddiff) return; // if busy or with bad params exit

  double ohmega; // angular velocity in terms of change in direction per second
                 // using dir: 0 = 0, 256 = 2pi
  milliseconds waittime; // wait time to travel dir angular distance

  direction += deltadir; // update the direction 

  speed &= 0x7f; // make sure the value is seven bits

  if (((int)speeddiff + this->speed) > 127)
    speeddiff = 127 - this->speed; // correct the speed diff if too high or low
  
  if (((int)this->speed - speeddiff) < -127)
    speeddiff = this->speed - 127;

  ohmega = ((int)speeddiff << 7) / (PI * WHEELBASE); // get tangential speed and convert it to angular

  waittime = milliseconds((uint64_t)(1000 * abs(deltadir) / ohmega)); // calculate wait time in millis

  busy = true;

  SetSpeed(LEFT, deltadir > 0 ? this->speed - speeddiff
                              : this->speed + speeddiff); // give the motors their new speeds
  
  SetSpeed(RIGHT, deltadir > 0 ? this->speed + speeddiff
                               : this->speed - speeddiff);

  this_thread::sleep_for(waittime); // wait until the turn has covered the delta

  SetSpeed(this->speed); // go back to going straight

  busy = false;

}

#endif