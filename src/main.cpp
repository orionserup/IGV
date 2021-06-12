/**
 * @file main.cpp
 * @brief Contains the Global Entry Point
 * @author Orion Serup
 * @bug None
 */
 
#include "IGV.hpp"
#include "test.hpp"
#include <string>

using namespace std;
using namespace cv;
using namespace igv;

/**
 * @brief Global Entry Point
 * @param argc Number of Arguments from CLI
 * @param argv Strings from the CLI
 * @returns int exit code
*/
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

  
#endif

  VideoCapture cap;

  cap.open(0);

  cap.set(3, 1280);
  cap.set(4, 720);

  Mat dest;

  cap >> dest;

  this_thread::sleep_for(100ms);

  cap >> dest;

  LaneDetector ld;

  ld.DetectLanes(dest);

  imshow("Captured Image", dest);
  waitKey(0);

  cap.release();

  // MotorController mc;

  // mc.SetSpeed(50);

  // //mc.ChangeDirection(64, 50);

  // this_thread::sleep_for(3s);

  return 0;

}



