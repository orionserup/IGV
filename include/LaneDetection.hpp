#pragma once

#include "opencv2/opencv.hpp"
#include "hal.hpp"

#define x 0
#define y 1

namespace igv{
struct Lane{

    double slope;
    uint32_t intercept;

};

uint32_t DetectLanes(std::array<Lane, 2>& LaneArray, Mat& image);

}


