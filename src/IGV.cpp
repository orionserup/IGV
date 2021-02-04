
#include "IGV.hpp"

using namespace igv;

IGV::IGV(HardwareInterface& hal): MC(hal){}

void IGV::Setup(){

  hal.LaneCam.Capture();
  hal.ultra.Probe();
  hal.ObjCam.Capture();
  hal.lidar.Probe();
  hal.gps.Probe();

}


void IGV::Run(){

  bool finished = false; 
  while(!finished){
    
    
    
  }
}
