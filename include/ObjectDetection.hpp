#pragma once

#include "opencv4/opencv2/opencv.hpp"
#include "hal.hpp"
#include <vector>

using namespace std;
using namespace cv;

struct Object{

    double distance;
    Direction angle;
    string classification;

};

class ObjectDetector{

public:

    ObjectDetector(HardwareInterface& hal);

    vector<Object>& ReadImage( unsigned char bytemask ) const;
    Mat* GetImage();

private:

    HardwareInterface& hal;
    vector<Object> objects;

};




