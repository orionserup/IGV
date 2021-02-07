
#include "IGV.hpp"

using namespace igv;
using namespace chrono;

IGV::IGV():LCam(USB1), OCam(USB2), LD(LCam), OD(OCam){}

void IGV::Setup(){

  LCam.Capture();
  us.Probe();
  OCam.Capture();
  lidar.Probe();
  gps.Probe();

}


void IGV::Run(){

  //thread ObjDet();
  //thread LaneDet(ODLoop);
  //thread Navigation(NavLoop);
  
  bool finished = false;
  while(!finished){
    
    
    
  }
}


