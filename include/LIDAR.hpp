/**
 * @file LIDAR.hpp
 * @brief Holds the Prototypes for the LIDAR Functionality
 * @author Orion Serup
 * @bug None
 */
#pragma once

#include "main.hpp"  // all custom types, std libraries and defines

#ifndef SIMULATION
#include "CppLinuxSerial/Exception.hpp"
#include "CppLinuxSerial/SerialPort.hpp"

using namespace mn::CppLinuxSerial;
#endif
using namespace std;

namespace igv{

/**
* @brief Container Class for LIDAR, acts as HAL
*/
class LIDAR{

public:

    /**
    * @brief Constructs a LIDAR Object
    */
    LIDAR();

    /**
    * @brief Probes the Surroundings and Writes the Data to a Map
    */  
    void Probe();
    
    /**
    * @brief Returns if the LIDAR is still probing
    * @returns bool: If the LIDAR is busy Probing
    */
    bool isBusy();
    
    /**
    * @brief Returns the Depth Map for the Surroundings
    * @return unordered_map<Direction, Distance> Depth Map
    */
    unordered_map<Direction, Distance>& GetMap() const { return mymap; }

private:
    
    #ifndef SIMULATION

    SerialPort myport;

    #endif

    bool busy;
    unordered_map<Direction, Distance> mymap;

}; 

}