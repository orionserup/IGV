/**
 * @file Camera.hpp
 * @brief Holds the Camera Implementation
 * @author Orion Serup
 * @bug None 
 */

#pragma once

#include "main.hpp"

using namespace cv;

/*@
 * \namespace igv
 * \brief Namespace for this project
 */
namespace igv{

/*!
 * \class Camera 
 * \brief Camera Container Class to hold and take images with
 */
class Camera {  // Camera Class, GetImage Calls to either ROS api or to the nano Camera API

    public:

        /*!
        * \fn Camera(int port)
        * \brief Opens a camera on the video port
        */ 
        Camera(int port);

        /*!
        * \fn inline Mat& GetImage()
        * \brief Gets the Captured Image
        */
        inline Mat& GetImage() { return Image; }
        
        /*!
        * \fn void Capture()
        * \brief Captures an image and puts it in the this->Image
        */
        void Capture();

    private:
        
        Mat Image;

        #ifndef SIMULATION

        VideoCapture cap;

        #endif
};

}
