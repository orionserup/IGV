#define SIMULATION

#include "IGV.hpp"

int main(const char** argv){  // run from the commnand line from SSH

    ObjectDetector detectors[NUMCAMERAS];
    HardwareInterface hal;
    MotorController mc;

    Initialize(detectors, hal, mc);
    Run(detectors, mc);

}

void Initialize(ObjectDetector* detectors, HardwareInterface& hal, MotorController& mc){

    for( int i = 0; i < )
        

}

