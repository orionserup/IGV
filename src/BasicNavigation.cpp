#include <BasicNavigation.hpp>

using namespace igv;

MotorController::MotorController(HardwareInterface &hal) : hal(hal) {

  direction = 0;
  speed = 0;
  busy = false;

}

/*

*/

void MotorController::SetSpeed(Speed speed) {

  hal.lmotor.SetSpeed(speed);
  hal.rmotor.SetSpeed(speed);

}

/* FUNCTION ChangeDirection:
 *
 * Completes a turn while moving, if speediff = current speed it turns in place
 * The slower the speed and faster the speeddiff the faster and less wide the
 * turn
 *
 * @params deltadir: change in direction, [0, 2pi] -> [0, 256]
 * @params speeddiff: How much to take off of the motor speed [0, 127]
 * @return void
 *
 */

void MotorController::ChangeDirection(DeltaDir deltadir, Speed speeddiff) {

  if (busy || deltadir == 0 || speeddiff == 0) return; // if busy or with bad params exit

  char currspeed = hal.lmotor.GetSpeed(); // get the current motor speed
  double ohmega; // angular velocity in terms of change in direction per second
                 // using dir: 0 = 0, 256 = 2pi
  milliseconds waittime; // wait time to travel dir angular distance

  direction = abs((uint8_t)direction + deltadir) & 0x7f; // update the direction so that its mag is not above 127

  speed &= 0x7f; // make sure the value is seven bits

  if (((int)speeddiff + currspeed) > 127)
    speeddiff = 127 - currspeed; // correct the speed diff if too high or low
  
  if (((int)currspeed - speeddiff) < -127)
    speeddiff = currspeed - 127;

  ohmega =
      ((int)speeddiff << 8) /
      (CV_PI * WHEELBASE); // get tangential speed and convert it to angular

  waittime = milliseconds((uint64_t)(1000 * abs(deltadir) /
                                     ohmega)); // calculate wait time in millis

  busy = true;

  hal.lmotor.SetSpeed(deltadir > 0 ? currspeed - speeddiff
                                  : currspeed + speeddiff); // give the motors their new speeds
  
  hal.rmotor.SetSpeed(deltadir > 0 ? currspeed + speeddiff
                                   : currspeed - speeddiff);

  this_thread::sleep_for(waittime); // wait until the turn has covered the delta

  SetSpeed(currspeed); // go back to going straight

  busy = false;

}
