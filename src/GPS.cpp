/**
 * @file GPS.cpp
 * @author Orion Serup
 * @brief Contains the GPS Functionality Implementation
 * @bug None
 */

#include "GPS.hpp"

#ifndef SIMULATION

using namespace mn::CppLinuxSerial;
using namespace igv;

GPS::GPS(): myport(GPSPORT, B9600){}

void GPS::Probe(){

}

Direction GPS::GetBearingTo(double lat, double lon){
    return this->gps.courseTo(this->CurrLat, this->CurrLong, lat, lon);
}

double GPS::GetDistanceTo(double lat, double lon){
    return this->gps.distanceBetween(this->CurrLat, this->CurrLong,lat,lon);
}

#else 


#endif