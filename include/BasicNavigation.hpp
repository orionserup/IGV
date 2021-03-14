#pragma once

#include "main.hpp"  // project defines

#ifndef SIMULATION
#include "CppLinuxSerial/SerialPort.hpp"
#include "CppLinuxSerial/Exception.hpp"

using namespace mn::CppLinuxSerial;
#endif

/**
 * @namespace igv
 * @brief IGV Global Namespace, holds all functionality
 */
namespace igv {

  /**
   * @class MotorController
   * @brief A controller for the motors, supplies external comm protocols 
   */

class MotorController{

public:

  /*!
  *  @brief Creates A Motor Controller Object
  */

  MotorController();  // by default the motor array comes from the HAL

  
  /*!
  *  @brief Completes a turn while moving 
  * 
  *  @param deltadir Change in direction, [0, 2pi] -> [0, 256]
  *  @param speeddiff How much to take off of the motor speed [0, 127]
  * 
  *  !The slower the speed and faster the speeddiff the faster and less wide the
  *  !turn
  */

  void ChangeDirection(DeltaDir deltadir, Speed speeddiff);  // changes the direction in motion
  
  /*!
  * @brief Sets the Speed of a motor
  * 
  * @param motor The Motor to Set the Speed of
  * @param speed The Speed to Set it to
  */
  
  void SetSpeed(Motor motor, Speed speed); // set the speed for one motor
 
  /*!
  * @brief Sets the Speed of both of the motors
  * 
  * @param speed The Speed to set it to [-127, 127]
  */

  void SetSpeed(Speed speed);  // set the speed for both motors
 
  /*!
   * @brief Goes in a certain direction with a certain speed for a distance
   * 
   * @param dist How far to go in meters
   * @param speed How fast to go, [-127, 127]
   * @param dir What Direction to Go in
   */
 
  void Go(Distance dist, Speed speed, Direction dir); // go dist meters, at speed speed in dir direction
    
  /*!
   * @brief Gets the Current Speed
   * 
   * @return Speed 
   */
  
  inline Speed GetSpeed() const { return this->speed; }  // gets the current speed
  
  /*!
   * @brief Get the Current Direction
   * 
   * @return Direction 
   */
  
  inline Direction GetDirection() const { return this->direction; } // gets the current direction
  
  /*!
   * @brief Checks if the MotorController is busy
   * 
   * @return bool 
   */

  inline bool isBusy() const { return busy; }

private:

  Direction direction;
  Speed speed;
  bool busy; 

  #ifndef SIMULATION

  SerialPort myport;

  #else

  #endif

};

}
