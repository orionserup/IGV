#pragma once

#include "opencv.hpp"
#include "hal.hpp"
#include <vector>

using namespace std;

class LaneDetector{

public:

    LaneDetector(HardwareInterface& hal);
    vector<Lane>& DetectLanes();

private:

    vector<Lane> Lanes;
    HardwareInterface& hal;

};

struct Lane{
    double slope;
    uint32_t xintercept;
};

