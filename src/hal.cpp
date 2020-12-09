#include "hal.hpp"

using namespace igv;

HardwareInterface::Camera::Camera(ID id) { 
    
    cap.open(id);
    
}

void HardwareInterface::Camera::Capture(){ 
    
    cap.grab();   // capture an image
    cap.retrieve(Image);  // get the image
    if(!Image.empty()) cvtColor(Image, Image, COLOR_BGR2HLS);
    
    
} 

void HardwareInterface::Motor::SetSpeed(Speed speed){

    //TODO 

}


void HardwareInterface::UltraSonic::Probe(){}

HardwareInterface::HardwareInterface(): LaneCam(USB), ObjCam(USB), lmotor(LEFT), rmotor(RIGHT){}

HardwareInterface::Motor::Motor(Location loc): myloc(loc){

    
}
