#pragma once

#include "main.hpp"
#ifndef SIMULATION
#include "JetsonGPIO.h"
#endif

class UltraSonic{

public:

    UltraSonic();
    double GetDistance(){ return this->distance; }  // returns the probed distance
    void Probe();  // gets a reading and puts it in the distance value
    bool isBusy() { return busy; }

private:

    bool busy;
    double distance;

};
