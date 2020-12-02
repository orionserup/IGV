#pragma once

#include "opencv2/opencv.hpp"
#include "hal.hpp"

#define x 0
#define y 1

struct Lane{

    double slope;
    int intercept;

};
class LaneDetector{

public:

    LaneDetector(HardwareInterface& hal);

    uint32_t DetectLanes(std::array<Lane, 2>& LaneArray);

private:

    HardwareInterface& hal;

};


