#include "LIDAR.hpp"

using namespace igv;

#ifndef SIMULATION
using namespace mn::CppLinuxSerial;

LIDAR::LIDAR(): myport(LIDARPORT, B9600){}

void LIDAR::Probe(){


}

#else



#endif