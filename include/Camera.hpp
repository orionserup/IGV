
#pragma once

#include "main.hpp"

using namespace cv;

namespace igv{

class Camera {  // Camera Class, GetImage Calls to either ROS api or to the nano Camera API

    public:

        Camera(int port);

        inline Mat& GetImage() { return Image; }
        void Capture();

    private:
        
        Mat Image;

        #ifndef SIMULATION

        VideoCapture cap;

        #endif
};

}
