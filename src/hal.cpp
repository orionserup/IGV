#include "hal.hpp"

#ifndef SIMULATION 

HardwareInterface::Camera::Camera(ID id): cap(id){}

HardwareInterface::Camera::~Camera(){}

void HardwareInterface::Camera::Capture(){ 
    
    cap >> Image;   // capture an image
    cvtColor(InputArray(Image), OutputArray(Image), COLOR_BGR2GRAY);  // make it grayscale
    
} 


void HardwareInterface::UltraSonic::Probe(){}

HardwareInterface::HardwareInterface(): LaneCam(USB), ObjCam(INT), lmotor(LEFT), rmotor(RIGHT){}



#else


#endif
