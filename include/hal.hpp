#include "opencv.hpp"
#include <array>

#define NUMCAMERAS 2
#define NUMMOTORS  4

#define IHEIGHT  480
#define IWIDTH   480

#define FR 30

using namespace std;
using namespace cv;

struct Camera{

    Camera();
    Mat GetImage();

};

class Motor{

public:

    Motor();
    Motor(Motor& motor);

    void Turn(char dir);
    void SetSpeed(char speed);

    char GetSpeed();
    char GetDirection();

private:

    char myspeed;
    char mydirection;

};

class HardwareInterface{

public:

    HardwareInterface(array<Camera, NUMCAMERAS>& Cameras, array<Motor, NUMMOTORS>& motors);
    HardwareInterface();

    void Init();

    void SetCamera(array<Camera, NUMCAMERAS>& cams);
    void SetMotors(array<Motor, NUMMOTORS>& motors);

    array<Camera, NUMCAMERAS>& GetCameras();
    array<Motor, NUMMOTORS>& GetMotors();

private:

    array<Camera, NUMCAMERAS> Cameras;
    array<Motor, NUMMOTORS> Motors;

};
