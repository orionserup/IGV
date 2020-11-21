#pragma once

#include "ObjectDetection.hpp"
#include "BasicNavigation.hpp"
#include "hal.hpp"

class IGV{

 public:

    IGV(HardwareInterface& hal);
    void Setup();
    void Run();

private:

    ObjectDetector objdetector;
    LaneDetector lanedetector;
    LIDAR lidar;
    MotorController MC;
}

