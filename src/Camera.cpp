/**
 * @file Camera.cpp
 * @author Orion Serup
 * @brief Contains the Implementation of the Camera Functionality
 * @bug None
 */

#include "Camera.hpp"
#ifndef SIMULATION

using namespace igv;

Camera::Camera(int port): cap(port) {}

void Camera::Capture() { cap >> this->Image; }

#else

#endif
