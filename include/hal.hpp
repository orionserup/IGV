#include "opencv.hpp"

#define CENTER 0
#define LEFT 0
#define RIGHT 1

#define FR 30

using namespace cv;

struct Location{   // struct for motor location

    enum side: char{left, right};
    enum balance : char{front, back};

};

class Camera {  // Camera struct, GetImage Calls to either ROS api or to the nano Camera API

public:

    Camera(int Location);

    inline Mat GetImage() const { return this->Image; }
    inline void Capture();

private:

    Mat Image;
    int Location;

};

class Motor{

public:

    Motor(Location loc);

    inline void SetSpeed(char speed) { this->myspeed = speed; }
    inline char GetSpeed() const { return this->myspeed; }

private:

    char myspeed;
    Location myloc;

};

struct HardwareInterface{

    HardwareInterface();

    Camera cam[NUMCAMERAS];
    Motor motors[NUMMOTORS];

};
