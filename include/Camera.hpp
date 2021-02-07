
#pragma once

#include "Defines.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;

namespace igv{

class Camera {  // Camera Class, GetImage Calls to either ROS api or to the nano Camera API

    public:

        Camera(ID id);

        inline Mat& GetImage() { return Image; }
        void Capture();

    private:
        
        Mat Image;

        #ifndef SIMULATION

        VideoCapture cap;

        #endif
};

}
