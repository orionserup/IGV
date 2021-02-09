#pragma once

#include "main.hpp"  // all custom types, std libraries and defines

#ifndef SIMULATION
#include "CppLinuxSerial/Exception.hpp"
#include "CppLinuxSerial/SerialPort.hpp"

using namespace mn::CppLinuxSerial;
#endif
using namespace std;

namespace igv{

class LIDAR{

public:

    LIDAR();
      
    void Probe();
    bool isBusy();
    unordered_map<Direction, Distance>& GetMap() { return mymap; }

private:
    
    #ifndef SIMULATION

    SerialPort myport;

    #endif

    bool busy;
    unordered_map<Direction, Distance> mymap;

}; 

}