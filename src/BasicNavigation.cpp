/**
 * @file BasicNavigation.cpp
 * @brief Contains the Motor Implementation
 * @author Orion Serup
 * @bug None
 */

#include "BasicNavigation.hpp"

using namespace igv;
using namespace std;
using namespace chrono;

void MotorController::SetSpeed(Speed speed){

  SetSpeed(LEFT, speed);
  SetSpeed(RIGHT, speed);

  this->speed = speed;

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

  waittime = milliseconds((uint64_t)(1000.0f * abs(deltadir) / ohmega)); // calculate wait time in millis

  busy = true;

  SetSpeed(LEFT, deltadir > 0 ? this->speed - speeddiff
                              : this->speed + speeddiff); // give the motors their new speeds
  
  SetSpeed(RIGHT, deltadir > 0 ? this->speed + speeddiff
                               : this->speed - speeddiff);

  this_thread::sleep_for(waittime); // wait until the turn has covered the delta

  SetSpeed(this->speed); // go back to going straight

  busy = false;

}

#ifndef SIMULATION

#ifdef SABERTOOTH

MotorController::MotorController() : 
  myport(MCPORT, B9600), busy(false), speed(0), direction(0){}

void MotorController::SetSpeed(Motor motor, Speed speed) {

  uint8_t* command = {0}
  uint8_t magnitude = abs(speed) >> 1;
  
  if (motor == LEFT)
    *command = speed < 0 ? 63 - magnitude : 64 + magnitude;
  
  else
    *command = speed < 0 ? 191 - magnitude : 192 + magnitude;
  
  *command = (!*command)? 1: (command == 0xff)? 254: command;
  
  this->myport.Write(command);

}

#endif

#ifdef PHIDGET

static void HandlePhidgetError();

MotorController::MotorController(const uint8_t leftport, const uint8_t rightport){

  //Create your Phidget channels
	PhidgetBLDCMotor_create(&this->left);
  PhidgetBLDCMotor_create(&this->right);

  //Set addressing parameters to specify which channel to open (if any)
	if(Phidget_setHubPort((PhidgetHandle)this->left, leftport) != EPHIDGET_OK)
    HandlePhidgetError();
  
  //Set addressing parameters to specify which channel to open (if any)
	if(Phidget_setHubPort((PhidgetHandle)this->right, rightport) != EPHIDGET_OK)
    HandlePhidgetError();

  Phidget_openWaitForAttachment((PhidgetHandle)this->right, 5500);
  Phidget_openWaitForAttachment((PhidgetHandle)this->left, 5500);


}

MotorController::MotorController(): MotorController(LEFTMOTORPORT, RIGHTMOTORPORT) {}


void MotorController::SetSpeed(const Motor motor, const Speed speed) {

  PhidgetBLDCMotorHandle bldc = motor == LEFT? this->left: this->right;
  Speed realspeed = motor == LEFT? speed: speed * -1;

  if(PhidgetBLDCMotor_setTargetVelocity(bldc, realspeed/128.0f) != EPHIDGET_OK)
    HandlePhidgetError();

}


MotorController::~MotorController() {

  //Close your Phidgets once the program is done.
  if(Phidget_close((PhidgetHandle)this->right) != EPHIDGET_OK) 
    HandlePhidgetError();

  //Close your Phidgets once the program is done.
  if(Phidget_close((PhidgetHandle)this->left) != EPHIDGET_OK) 
    HandlePhidgetError();

  PhidgetBLDCMotor_delete(&this->left);
  PhidgetBLDCMotor_delete(&this->right);

}


void HandlePhidgetError() {
    
  PhidgetReturnCode errorCode;
	const char * errorString;
	char errorDetail[100];
	size_t errorDetailLen = 100;

  Phidget_getLastError(&errorCode, &errorString, errorDetail, &errorDetailLen);
	cout << "Error" << errorCode << ": " << errorString;

}

#endif

#endif
