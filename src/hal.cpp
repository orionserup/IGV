#include "hal.hpp"

using namespace igv;

HardwareInterface::Camera::Camera(ID id) { 
    
    cap.open(id);
    
}

HardwareInterface::Camera::Camera(VideoCapture& capture){
    cap = capture;
}

void HardwareInterface::Camera::Capture(){ 
    
    if(cap.isOpened()){
        cap.grab();   // capture an image
        cap.retrieve(Image);  // get the image
        if(!Image.empty()) cvtColor(Image, Image, COLOR_BGR2GRAY);
    }

} 

void HardwareInterface::Motor::SetSpeed(Speed speed){

    //TODO 

}


void HardwareInterface::UltraSonic::Probe(){}

HardwareInterface::HardwareInterface(): 
    lanecam(USB), objcam(USB), lmotor(LEFT), rmotor(RIGHT), LaneCam(lanecam), ObjCam(objcam){}

HardwareInterface::Motor::Motor(Location loc): myloc(loc){}
