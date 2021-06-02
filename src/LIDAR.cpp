/**
 * @file LIDAR.cpp
 * @brief Constains all of the LIDAR functionality
 * @author Orion Serup
 * @bug None
 */

#include "LIDAR.hpp"

using namespace igv;
using namespace ydlidar;

#ifndef SIMULATION

LIDAR::LIDAR(){

    mylidar.initialize();

    mylidar.setSerialPort(LIDARPORT);
    mylidar.setSerialBaudrate(115200); // port at 115200 baud

    mylidar.setScanFrequency(1); // 1Hz scan rate
    mylidar.setSampleRate(1000);

    mylidar.setMinAngle(0);
    mylidar.setMaxAngle(120);
    
    mylidar.setMinRange(1.0f);
    mylidar.setMaxRange(10.0f);

    mylidar.setReversion(false);
    mylidar.setIntensities(true);

    mylidar.turnOn();

}

void LIDAR::Probe(){

    bool error;
    if(!mylidar.doProcessSimple(scan, error))
        cout << "LIDAR Cannot Scan";

}

#else



#endif
