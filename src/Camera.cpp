
#include "Camera.hpp"
#ifndef SIMULATION

using namespace igv;

Camera::Camera(ID id) : cap(id) {}

void Camera::Capture() { cap >> this->Image; }

#else

#endif
