#include "hal.hpp"


HardwareInterface::Camera::Camera(ID id): cap(id){}

HardwareInterface::Camera::~Camera(){}

void HardwareInterface::Camera::Capture(){ 
    
    cap >> Image;   // capture an image
    cvtColor(InputArray(Image), OutputArray(Image), COLOR_BGR2GRAY);  // make it grayscale
    
} 

void HardwareInterface::Motor::SetSpeed(Speed speed){

    //TODO 

}


void HardwareInterface::UltraSonic::Probe(){}

HardwareInterface::HardwareInterface(): LaneCam(USB), ObjCam(INT), lmotor(LEFT), rmotor(RIGHT){}

HardwareInterface::Motor::Motor(Location loc): myloc(loc){

    
}
