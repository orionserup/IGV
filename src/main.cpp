
#include "IGV.hpp"
#include "test.hpp"
#include <string>

using namespace std;
using namespace cv;
using namespace igv;

int main(int argc, char** argv){

#ifdef DEBUG

  if(argc > 1){

    if(!(string(argv[1])).compare("--setup")){

      IGV igv;
      igv.Setup();

    }

    else{

      cout << "Testing Window" << endl;

      Test test("../test/test.log");

      if(argc > 2){
      
        string obj, filename;

        for(int i = 2; i < argc; i++){
        
          obj = argv[i];
        
          if(!obj.compare("all"))           test.RunAllTests();
          else if(!obj.compare("cam"))      test.CameraTest();
          else if(!obj.compare("motor"))    test.MotorTest();
          else if(!obj.compare("od"))       test.ObjectDetectionTest();
          else if(!obj.compare("ld"))       test.LaneDetectionTest("../test/test.jpeg");
          else if(!obj.compare("lidar"))    test.LIDARTest();
          else if(!obj.compare("gps"))      test.GPSTest();
          else cout << "Invalid Option: " << obj << endl;
      
        } 
      }
    }
  }

  else 
    cout  << "Welcome to the IGV Help Menu\n"
          << "'--test' Runs the Tests to specify which one put options after:\n"
          << "\t'cam', 'gps', 'all', 'motor', 'lidar', 'ld', 'od', 'sensors'\n";

    
  return EXIT_SUCCESS;
  
#endif

  IGV igv;

  igv.Setup();
  igv.Run();

}


