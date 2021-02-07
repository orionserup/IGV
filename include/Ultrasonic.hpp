#pragma once

#include "Defines.hpp"
#ifndef SIMULATION
#include "JetsonGPIO.h"
#endif

class UltraSonic{

public:

    double GetDistance(){ return this->distance; }  // returns the probed distance
    void Probe();  // gets a reading and puts it in the distance value

private:

    double distance;

};
