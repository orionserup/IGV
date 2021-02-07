#pragma once

#include <unordered_map>
#include "Defines.hpp"

#ifndef SIMULATION
#include "CppLinuxSerial/Exception.hpp"
#include "CppLinuxSerial/SerialPort.hpp"

using namespace mn::CppLinuxSerial;
#endif
using namespace std;

namespace igv{

class LIDAR{

public:
      
    void Probe();

private:
    
    #ifndef SIMULATION

    SerialPort myport;

    #endif

    unordered_map<Direction, Distance> mymap;

}; 

}