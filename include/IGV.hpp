#pragma once

#include "ObjectDetection.hpp"
#include "BasicNavigation.hpp"
#include "LaneDetection.hpp"
#include "hal.hpp"

namespace igv{

class IGV{

 public:

    IGV(HardwareInterface& hal);

    void Setup();
    void Run();

private:

    MotorController MC;
    HardwareInterface hal;

};

}
