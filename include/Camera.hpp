/**
 * @file Camera.hpp
 * @brief Holds the Camera Implementation
 * @author Orion Serup
 * @bug None 
 */

#pragma once

#include "main.hpp"

using namespace cv;

/**
 * @namespace igv
 * @brief Namespace for this project
 */
namespace igv{

/**
 * @class Camera 
 * @brief Camera Container Class to hold and take images with
 */
class Camera {  // Camera Class, GetImage Calls to either ROS api or to the nano Camera API

    public:

        /**
        * @fn Camera
        * @brief Constructs Camera from the Video Port
        * @param port Video Port to Open
        */ 
        Camera(int port);

        /*!
        * @fn inline Mat& GetImage()
        * @brief Gets the Captured Image
        * @returns Stored Image
        */
        inline Mat& GetImage() { return Image; }
        
        /**
        * @fn Capture()
        * @brief Captures an image and puts it in the Image
        */
        void Capture();

    private:
        
        Mat Image;

        #ifndef SIMULATION

        VideoCapture cap;

        #endif
};

}
