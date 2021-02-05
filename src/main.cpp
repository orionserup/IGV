
#include "IGV.hpp"

#define LaneCamFPS 10
#define ObjCamFPS  10
#define NavRefRate 10

using namespace std;
using namespace cv;
using namespace igv;

void LDLoop(HardwareInterface::Camera& cam, array<Lane, 2>& lanes);
void ODLoop(HardwareInterface::Camera& cam, vector<Object>& objs);
void NavLoop(MotorController& MC, vector<Object>& objs, array<Lane, 2>& lanes);

int main(int argc, const char** argv){
  
  IGV igv;

  igv.Setup();
  igv.Run();

}

/*
void LDLoop(HardwareInterface::Camera& cam, std::array<Lane, 2>& lanes){

  while(1){

    cam.Capture();
    Mat& image = cam.GetImage();
    DetectLanes(lanes, image);
    this_thread::sleep_for(milliseconds(1000/LaneCamFPS));

  }
}

void ODLoop(HardwareInterface::Camera& cam, std::vector<Object>& objs){

  while(1){

    cam.Capture();
    Mat& image = cam.GetImage();
    DetectObjects(objs, image);
    this_thread::sleep_for(milliseconds(1000/ObjCamFPS));
  
  }
}

void NavLoop(MotorController& MC, std::vector<Object>& objs, std::array<Lane, 2>& lanes){

  Direction dir = MC.GetDirection();
  Speed speed = MC.GetSpeed();
  
  while(1){

    

    
    this_thread::sleep_for(milliseconds(1000/NavRefRate));

  }
}
*/