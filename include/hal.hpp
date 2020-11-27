#pragma once

#include "opencv4/opencv2/opencv.hpp"
#include <string>

#define CENTER 0
#define LEFT 0
#define RIGHT 1

#define USB 0
#define DCIM 1

#define NUMCAMERAS 1
#define NUMMOTORS  2
#define NUMLIDARS  1
#define NUMULTRAS  2

#define SIM_MODE  0
#define NORM_MODE 1

#define IHEIGHT  480
#define IWIDTH   480

#define FR 30

#define WHEELBASE (float)31.0f

using namespace cv;
using namespace std;


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

        Camera(uint32_t id): identifier(id){}

        inline Mat* GetImage() const { return this->Image; }
        void Capture();

    private:

        Mat* Image;
        uint32_t identifier;

    };

    class Motor{

    public:

        Motor(int Location);

        void SetSpeed(char speed);
        inline char GetSpeed() const { return this->myspeed; } 
        inline int GetLocation() const { return this->myloc; }

    private:

        char myspeed;
        int myloc;

    };

    class LIDAR{

    public:
        LIDAR(HardwareInterface& hal);
        

    }; 

    class UltraSonic{

    public:

        UltraSonic(HardwareInterface& hal);
        double GetDistance(){ return this->distance; }  // returns the probed distance
        void Probe();  // gets a reading and puts it in the distance value

    private:

        double distance;

    };

    HardwareInterface(char MODE);  // initializes the hardware interface, IO, etc

    Camera cam[NUMCAMERAS];       // the interface holds the cameras,
    Motor motor[NUMMOTORS];       // motors,
    LIDAR lidar[NUMLIDARS];       // lidar,
    UltraSonic us[NUMULTRAS];     // and UltraSonic Sensors so that the other modules can control peripherals without IO manip

};
