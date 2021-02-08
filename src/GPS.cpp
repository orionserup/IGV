#include "GPS.hpp"

#ifndef SIMULATION
using namespace mn::CppLinuxSerial;

GPS::GPS(): myport(GPSPORT, B9600){}

void GPS::Probe(){





}



#else 


#endif