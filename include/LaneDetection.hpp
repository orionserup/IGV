#pragma once

#include "opencv2/opencv.hpp"
#include "hal.hpp"
namespace igv{
struct Lane{

    double slope;
    uint32_t intercept;

    friend ostream& operator<<(ostream& os, const Lane& lane);

};

uint32_t DetectLanes(std::array<Lane, 2>& LaneArray, Mat& image);

}


