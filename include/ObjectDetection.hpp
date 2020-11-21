#pragma once
 
#define HAVE_OPENCV_IMGPROC
#define HAVE_OPENCV_PHOTO

#include "opencv.hpp"
#include "hal.hpp"
#include <vector>

using namespace std;
using namespace cv;

struct Object{

    double distance;
    char angle;
    string classification;

};

class ObjectDetector{

public:

    ObjectDetector(HardwareInterface& hal);

    vector<Object>& ReadImage( unsigned char bytemask ) const;
    Mat& GetImage( int Loc = 0 ) { return hal.cam[Loc].GetImage(); }

private:

    HardwareInterface& hal;
    vector<Object> objects;

};




