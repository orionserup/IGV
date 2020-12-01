#pragma once

#include "opencv4/opencv2/opencv.hpp"
#include <string>
#include <array>

#define WHEELBASE (float)31.0f

using namespace cv;
using namespace std;

enum Location: char{LEFT = 0, RIGHT = 1};
enum ID : unsigned char{INT = 0, USB = 1};


/* Hardware Interface Structure
*
*   FUNCTIONALITY:  Acts as a middle man between the Software and the Hardware, Almost a firmware of sorts
*   CONTAINS:       Holds Objects connected to hardware, they can be accessed using hal.object[index].function() or HardwareInterface::Object::Function()
*   DEPENDENCIES:   Has no Depencies other than just typename dependencies from namespace cv and std
*   
*/ 

class HardwareInterface{  

public:
    class Camera {  // Camera struct, GetImage Calls to either ROS api or to the nano Camera API

    public:

        Camera(ID id);
        Camera() = default;
        ~Camera();

        inline Mat GetImage() const { return this->Image; }
        void Capture();

    private:
        
        Mat Image;
        VideoCapture cap;

    };

    class Motor{

    public:

        Motor(Location loc);
        Motor() = default;
        ~Motor();

        void SetSpeed(char speed);
        inline char GetSpeed() const { return this->myspeed; } 
        inline int GetLocation() const { return this->myloc; }

    private:

        char myspeed;
        Location myloc;

    };

    class LIDAR{

    public:

        LIDAR();
        ~LIDAR();
        

    }; 

    class UltraSonic{

    public:

        UltraSonic();
        ~UltraSonic();

        double GetDistance(){ return this->distance; }  // returns the probed distance
        void Probe();  // gets a reading and puts it in the distance value

    private:

        double distance;

    };

    HardwareInterface();        // initializes the hardware interface, IO, etc

    Camera LaneCam, ObjCam;     // the interface holds the cameras,
    Motor lmotor, rmotor;       // motors,
    LIDAR lidar;                // lidar,
    UltraSonic ultra;           // and UltraSonic Sensors so that the other modules can control peripherals without IO manip

};
