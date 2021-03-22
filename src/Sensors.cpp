/**
 * @file Sensors.cpp
 * @author Orion Serup
 * @brief Contains all of the Sensor Functionality Implementation
 * @bug None 
 */

#include "Sensors.hpp"

#ifndef SIMULATION
using namespace mn::CppLinuxSerial;
using namespace igv;

void Magno::Probe(){

}

UltraSonic::UltraSonic(){

    GPIO::setmode(GPIO::BOARD);

    GPIO::setup(ULTRA_IN, GPIO::IN);
    GPIO::setup(ULTRA_OUT, GPIO::OUT, GPIO::LOW);

}

void UltraSonic::Probe() {
    
    busy = true;

    GPIO::output(ULTRA_OUT, GPIO::HIGH);  // trigger a pulse
    auto start = std::chrono::system_clock::now();  // get the current time
    while(!GPIO::input(ULTRA_IN));  // wait for a signal on the input line
    auto end = std::chrono::system_clock::now();  // get the current time

    std::chrono::duration<double> timediff = end - start; // calculate the difference

    this->distance = VSOUND_D2*timediff.count(); // v = d/t -> d = v*t: t = timediff/2, v = speed of sound
    GPIO::output(ULTRA_OUT, GPIO::LOW);  // reset

    busy = false;

}


#else 


#endif