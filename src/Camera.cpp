
#include "Camera.hpp"
#ifndef SIMULATION

using namespace igv;

Camera::Camera(int port): cap(port) {}

void Camera::Capture() { cap >> this->Image; }

#else

#endif
