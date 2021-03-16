/**
 * @file LIDAR.cpp
 * @brief Constains all of the LIDAR functionality
 * @author Orion Serup
 * @bug None
 */

#include "LIDAR.hpp"

using namespace igv;

#ifndef SIMULATION
using namespace mn::CppLinuxSerial;

LIDAR::LIDAR(): myport(LIDARPORT, B9600){}

void LIDAR::Probe(){


}

#else



#endif