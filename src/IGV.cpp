
#include "IGV.hpp"

int main(const char** argv){  // run from the commnand line from SSH

    HardwareInterface hal;
    IGV vehicle(hal);

    vehicle.Setup();
    vehicle.Run();

    return 0;

}

IGV::IGV(HardwareInterface& hal) {

    MotorController mc(hal);
    LIDAR lidar(hal);
    ObjectDetector OD(hal);
    LaneDetector LD(hal);

     

    
    
     
}