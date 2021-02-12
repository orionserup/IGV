#include "Ultrasonic.hpp"

using namespace std;

#ifndef SIMULATION

UltraSonic::UltraSonic(){

    GPIO::setup(ULTRA_IN, GPIO::IN);
    GPIO::setup(ULTRA_OUT, GPIO::OUT);

}

void UltraSonic::Probe() {
    
    busy = true;

    GPIO::output(ULTRA_OUT, GPIO::HIGH);  // trigger a pulse
    auto start = chrono::system_clock::now();  // get the current time
    while(!GPIO::input(ULTRA_IN));  // wait for a signal on the input line
    auto end = chrono::system_clock::now();  // get the current time

    chrono::duration<double> timediff = end - start; // calculate the difference

    this->distance = VSOUND_D2*timediff.count(); // v = d/t -> d = v*t: t = timediff/2, v = speed of sound
    GPIO::output(ULTRA_OUT, GPIO::LOW);  // reset

    busy = false;

}

#else

#endif