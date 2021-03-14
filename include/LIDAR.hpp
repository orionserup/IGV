#pragma once

#include "main.hpp"  // all custom types, std libraries and defines

#ifndef SIMULATION
#include "CppLinuxSerial/Exception.hpp"
#include "CppLinuxSerial/SerialPort.hpp"

using namespace mn::CppLinuxSerial;
#endif
using namespace std;

/*!
* \namespace igv
* \brief Namespace for this project
*/
namespace igv{

/*!
* \class LIDAR
* \brief Container Class for LIDAR, acts as HAL
*/
class LIDAR{

public:

    /*!
    * \fn LIDAR()
    * \brief Constructs a LIDAR Object
    */
    LIDAR();

    /*!
    * \fn Probe()
    * \brief Probes the Surroundings and Writes the Data to a Map
    */  
    void Probe();
    
    /*!
    * \fn isBusy()
    * \brief Returns if the LIDAR is still probing
    * \returns bool
    */
    bool isBusy();
    
    /*!
    * \fn GetMap()
    * \brief Returns the Depth Map for the Surroundings
    * \return unordered_map<Direction, Distance>&
    */
    unordered_map<Direction, Distance>& GetMap() { return mymap; }

private:
    
    #ifndef SIMULATION

    SerialPort myport;

    #endif

    bool busy;
    unordered_map<Direction, Distance> mymap;

}; 

}