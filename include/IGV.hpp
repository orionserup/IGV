#pragma once

#include "ObjectDetection.hpp"
#include "BasicNavigation.hpp"
#include "LaneDetection.hpp"
#include "hal.hpp"

#include <list>
#include <thread>
namespace igv{
class IGV{

public:

  IGV(HardwareInterface& hal);
  IGV();

  void Setup();
  void Run();

private:

  MotorController MC;
  HardwareInterface hal;
    
};

}
