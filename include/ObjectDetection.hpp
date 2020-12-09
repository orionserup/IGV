#pragma once

#include "opencv2/opencv.hpp"
#include "hal.hpp"
#include <vector>

using namespace std;
using namespace cv;

namespace igv {

struct Object{

    double distance;
    Direction angle;
    string classification;

};

uint32_t DetectObjects(vector<Object> &objects, Mat& Image);

}



