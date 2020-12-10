
#include "IGV.hpp"
#include <iostream>
#include <fstream>

class Test{

public:

    Test(const char* logfile);
    Test();
    ~Test();

    bool OpenLogFile(const char* logfile);
    bool Ready();

    bool RunAllTests();

    bool CameraTest();
    bool MotorTest();
    bool LIDARTest();
    bool USTest();
    bool LaneDetectionTest();
    bool ObjectDetectionTest();

private:

    ofstream logfile;

};