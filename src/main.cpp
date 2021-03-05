
#include "IGV.hpp"
#include "test.hpp"
#include <string>

using namespace std;
using namespace cv;
using namespace igv;

int main(int argc, char** argv){

  if(argc > 1){
    
    cout << "Testing Window" << endl;

    Test test("../test/test.log");

    if(argc > 2){
      
      string obj;

      for(int i = 2; i < argc; i++){
        
        obj = argv[i];

        cout << obj << endl;

        if(!obj.compare("all"))           test.RunAllTests();
        else if(!obj.compare("cam"))      test.CameraTest();
        else if(!obj.compare("motor"))    test.MotorTest();
        else if(!obj.compare("od"))       test.ObjectDetectionTest();
        else if(!obj.compare("ld"))       test.LaneDetectionTest();
        else if(!obj.compare("sensors"))  test.SensorsTest();
        else if(!obj.compare("lidar"))    test.LIDARTest();
        else if(!obj.compare("gps"))      test.GPSTest();
        else cout << "Invalid Option: " << obj << endl;
      
      } 
    }

    else 
    cout  << "Welcome to the IGV Help Menu\n"
          << "'--test' Runs the Tests to specify which one put options after:\n"
          << "\t'cam', 'gps', 'all', 'motor', 'lidar', 'ld', 'od', 'sensors'\n";
  
  }

  else{

    IGV igv;

    igv.Setup();
    igv.Run();

  }
}


