#define SIMULATION 

#include "IGV.hpp"

int main(int argc, const char** argv){

    HardwareInterface hal;
    IGV vehicle(hal);

    vehicle.Setup();
    vehicle.Run();

}