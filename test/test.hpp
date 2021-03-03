
#include "IGV.hpp"
#include <iostream>
#include <fstream>

class Test{

public:

    Test(const char* logfile);
    Test() = default;
    ~Test();

    bool OpenLogFile(const char* logfile);
    bool Ready();

    bool RunAllTests();

    bool CameraTest();
    bool MotorTest();
    bool LIDARTest();
    bool GPSTest();
    bool AccelerometerTest();
    bool USTest();
    bool LaneDetectionTest();
    bool ObjectDetectionTest();

private:

    ofstream logfile;

};
