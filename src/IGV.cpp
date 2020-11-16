#define SIMULATION

#include "IGV.hpp"

int main(const char** argv){  // run from the commnand line from SSH

    vector<ObjectDetector> detectors;
    HardwareInterface hal;

    Initialize(detectors, hal);
    run(detectors);

}

void Initialize(vector<ObjectDetector>& detectors, HardwareInterface& hal){

    hal.Init();
        

}