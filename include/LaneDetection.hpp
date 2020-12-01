#pragma once

#include "opencv.hpp"
#include "hal.hpp"

#define x 0
#define y 1

using namespace std;

struct Lane{

    double slope;
    uint32_t intercept;

};
class LaneDetector{

public:

    LaneDetector(HardwareInterface& hal);
    ~LaneDetector();

    uint32_t DetectLanes(array<Lane, 2>& LaneArray);

private:

    HardwareInterface& hal;

};


