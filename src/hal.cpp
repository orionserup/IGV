#ifndef SIMULATION
#include "hal.hpp"

using namespace igv;

HardwareInterface::Camera::Camera(ID id) : cap(id) {}

HardwareInterface::Camera::Camera(VideoCapture &capture) : cap(capture) {}

void HardwareInterface::Camera::Capture() {

  cap >> Image;

}

void HardwareInterface::Motor::SetSpeed(Speed speed) {

  // TODO
}

void HardwareInterface::UltraSonic::Probe() {}

HardwareInterface::HardwareInterface()
    : LaneCam(INT), ObjCam(USB), lmotor(LEFT), rmotor(RIGHT) {}

HardwareInterface::Motor::Motor(Location loc) : myloc(loc) {}

void HardwareInterface::GPS::Probe(){}

void HardwareInterface::LIDAR::Probe(){}

#endif
