#pragma once

#include "main.hpp"  // project defines

#ifndef SIMULATION
#include "CppLinuxSerial/SerialPort.hpp"
#include "CppLinuxSerial/Exception.hpp"

using namespace mn::CppLinuxSerial;
#endif

/*!
 * \namespace igv
 * \brief IGV Global Namespace, holds all functionality
 */
namespace igv {

  /*!
   * \class MotorController
   * \brief A controller for the motors, supplies external comm protocols 
   * 
   * A motor controller is in charge of all fo the movemement of the robot.
   * It is interfaced with using a UART Serial bridge and is a Sabertooth 
   * Motor Controller
   * 
   */
class MotorController{

public:

  /*!
  *  \fn MotorController::MotorController()
  *  \brief Creates A Motor Controller Object
  */
  MotorController();  // by default the motor array comes from the HAL

  
  /*!
  *  \fn void MotorController::ChangeDirection(DeltaDir deltadir, Speed speeddiff)
  *  \brief Turns the vehicle while moving 
  * 
  *  The slower the speed and faster the speeddiff the faster and less wide the
  *  turn
  */
  void ChangeDirection(DeltaDir deltadir, Speed speeddiff);  // changes the direction in motion
  
  /*!
  * \fn void SetSpeed(Motor motor, Speed speed)
  * \brief Sets the Speed of a motor
  */
  void SetSpeed(Motor motor, Speed speed); // set the speed for one motor
 
  /*!
  * \fn void SetSpeed(Speed speed)
  * \brief Sets the Speed of both of the motors
  */
  void SetSpeed(Speed speed);  // set the speed for both motors
 
  /*!
   * \fn void Go(Distance dist, Speed speed, Direction dir)
   * \brief Goes in a certain direction with a certain speed for a distance
   */
  void Go(Distance dist, Speed speed, Direction dir); // go dist meters, at speed speed in dir direction
    
  /*!
   * \fn Speed GetSpeed() const
   * \brief Gets the Current Speed
   * 
   */
  inline Speed GetSpeed() const { return this->speed; }  // gets the current speed
  
  /*!
   * \fn Direction GetDirection() const
   * \brief Get the Current Direction
   */
  
  inline Direction GetDirection() const { return this->direction; } // gets the current direction
  
  /*!
   * \fn bool isBusy()
   * \brief Checks if the MotorController is busy
   * 
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
