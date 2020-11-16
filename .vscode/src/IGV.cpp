#define SIMULATION

#include "IGV.hpp"

int main(const char** argv){  // run from the commnand line from SSH

    vector<ObjectDetector> detectors;
    HardwareInterface hal;

    Initialize(detectors, hal);
    run(detectors);

}

void Initialize(vector<ObjectDetector>& detectors, HardwareInterface& hal){

    Mat 

    hal.Init();
    for(int i = 0; i < hal.GetCameras().size(); i++){

        detectors[i].SetCamera(hal.GetCameras()[i]);
        detectors[i].CaptureImage();

    }

    

}