#pragma once

#include "ObjectDetection.hpp"
#include "BasicNavigation.hpp"
#include "LaneDetection.hpp"
#include "hal.hpp"

class IGV{

 public:

    IGV(HardwareInterface& hal);
    void Setup();
    void Run();

private:

    ObjectDetector objdetector;
    LaneDetector lanedetector;
    MotorController MC;
};

