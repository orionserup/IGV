
#include "IGV.hpp"

int main(string[] argv){  // run from the commnand line from SSH

    HardwareInterface hal(NORM_MODE);
    IGV vehicle(hal);

    vehicle.Setup();
    vehicle.Run();

    return 0;

}

IGV::IGV(HardwareInterface& hal): lanedetector(hal), objdetector(hal), MC(hal), lidar(hal), us(hal){




     

    
    
     
}