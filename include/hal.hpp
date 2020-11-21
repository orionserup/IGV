#pragma once

#include "opencv.hpp"

#define CENTER 0
#define LEFT 0
#define RIGHT 1

#define NUMCAMERAS 1
#define NUMMOTORS  2

#define IHEIGHT  480
#define IWIDTH   480

#define FR 30

#define WHEELBASE (float)10.4f

#define SIMULATION

using namespace cv;


class Camera {  // Camera struct, GetImage Calls to either ROS api or to the nano Camera API

public:

    Camera(int Location);

    inline Mat* GetImage() const { return this->Image; }
    void Capture();

private:

    Mat* Image;
    string designator;

};

class Motor{

public:

    Motor(int Location);

    void SetSpeed(char speed);
    inline char GetSpeed() const { return myspeed; } 

private:

    char myspeed;
    int myloc;

};

class LIDAR{

}; 

class UltraSonic{};

struct HardwareInterface{

    HardwareInterface();

    Camera cam[NUMCAMERAS];
    Motor motors[NUMMOTORS];
    LIDAR lidars[];
    UltraSonic us[];

};
