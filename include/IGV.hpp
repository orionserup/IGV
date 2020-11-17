#pragma once

#include "ObjectDetection.hpp"
#include "BasicNavigation.hpp"
#include "hal.hpp"

void Initialize(ObjectDetector* detectors, HardwareInterface& hal , MotorController& mc);
void Run(ObjectDetector* detector, MotorController& mc);

