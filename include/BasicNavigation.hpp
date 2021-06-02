
/**
 * @file BasicNavigation.hpp
 * @brief Contains all Driving Functionality
 * @author Orion Serup
 * @bug None
 */

#pragma once
#include "main.hpp"  // project defines

#ifndef SIMULATION

#ifdef SABERTOOTH
#include "CppLinuxSerial/SerialPort.hpp"
#include "CppLinuxSerial/Exception.hpp"

using namespace mn::CppLinuxSerial;

#elif defined(PHIDGET)

#include "phidget22.h"

#endif

#endif

/**
 * @namespace igv
 * @brief IGV Global Namespace, holds all functionality
 */
namespace igv {

/**
  * @class MotorController
  * @brief A controller for the motors, supplies external comm protocols 
  * 
  * A motor controller is in charge of all fo the movemement of the robot.
  * It is interfaced with using a UART Serial bridge and is a Sabertooth 
  * Motor Controller.
  * 
  */
class MotorController{

public:

  /**
  *  @fn MotorController()
  *  @brief Creates A Motor Controller Object
  */
  MotorController();  // by default the motor array comes from the HAL

  /**
  * @brief Destroy the Motor Controller object
  * 
  */
  ~MotorController();

  #ifdef PHIDGET

  /**
   * @brief  Creates a Motor Controller Object for the Phidget Implementation
   * @param  leftport: The Hub port of the left motor
   * @param  rightport: The Hub port of the right motor
   */
  MotorController(const uint8_t leftport, const uint8_t rightport);

  #endif

  
  /**
  *  @fn ChangeDirection(DeltaDir deltadir, Speed speeddiff)
  *  @brief Turns the vehicle while moving
  *  @param deltadir How much to turn
  *  @param speeddiff How Tight and Fast the turn 
  * 
  *  The slower the speed and faster the speeddiff the faster and less wide the
  *  turn.
  */
  void ChangeDirection(DeltaDir deltadir, Speed speeddiff);  // changes the direction in motion
  
  /**
  * @fn void SetSpeed(Motor motor, Speed speed)
  * @brief Sets the Speed of a motor
  * @param motor Which Motor to Write to
  * @param speed What speed to set it to
  */
  void SetSpeed(Motor motor, Speed speed); // set the speed for one motor
 
  /**
  * @fn void SetSpeed(Speed speed)
  * @brief Sets the Speed of both of the motors
  * @param speed How Fast to Go
  */
  void SetSpeed(Speed speed);  // set the speed for both motors
 
  /**
   * @fn void Go(Distance dist, Speed speed, Direction dir)
   * @brief Goes in a certain direction with a certain speed for a distance
   * @param dist How Far to Go
   * @param speed How Fast to Go
   * @param dir What Direction To Go In
   */
  void Go(Distance dist, Speed speed, Direction dir); // go dist meters, at speed speed in dir direction
    
  /**
   * @fn GetSpeed()
   * @brief Gets the Current Speed
   * @returns Speed, the current speed
   */
  inline Speed GetSpeed() const { return this->speed; }  // gets the current speed
  
  /**
   * @fn GetDirection()
   * @brief Get the Current Direction
   * @returns Direction, the Current Direction Heading
   */
  inline Direction GetDirection() const { return this->direction; } // gets the current direction
  
  /**
   * @fn isBusy()
   * @brief Checks if the MotorController is busy
   * @returns bool: if the MotorController is busy with an operation
   */
  inline bool isBusy() const { return busy; }

private:

  Direction direction;
  Speed speed;
  bool busy; 

  #ifndef SIMULATION

  #ifdef SABERTOOTH

  SerialPort myport;

  #elif defined(PHIDGET)

  PhidgetBLDCMotorHandle left, right; // left and right motors

  #endif

  #endif

};

}
