
#include "test.hpp"

using namespace std;
using namespace cv;
using namespace igv;

Test::Test(const char* logfile): logfile(logfile){}

Test::~Test(){ logfile.close(); }

bool Test::CameraTest(){

    bool Passed = true;

    logfile << "Creating Lane Camera Object \n";
    Camera cam1(LANECAMPORT);

    logfile << "Taking a Picture \n";
    cam1.Capture();

    logfile << "Retrieving the Image \n";
    Mat testimage = cam1.GetImage();

    logfile <<  "Image Specs: \n" <<
                "=========================" << 
                "Is Empty:       " << testimage.empty() << endl << 
                "Dimensionality: " << testimage.dims << endl <<
                "Pixel Format:   " << testimage.depth() << endl <<
                "Size:           " << testimage.size << endl << endl;


    if(testimage.empty() || !testimage.size) Passed = false;
    else Passed = true;

    logfile << "Creating Object Camera Object \n";
    Camera cam2(OBJCAMPORT);

    logfile << "Taking a Picture: \n";
    cam2.Capture();

    logfile << "Retrieving the Image \n";
    logfile <<  "Image Specs: \n" <<
                "=========================" << 
                "Is Empty:       " << testimage.empty() << endl << 
                "Dimensionality: " << testimage.dims << endl <<
                "Pixel Format:   " << testimage.depth() << endl <<
                "Size:           " << testimage.size << endl << endl << endl;


    if(testimage.empty() || !testimage.size) Passed = false;
    else Passed = true;

    return Passed;
}

bool Test::LaneDetectionTest(){

  bool passed = true;

  LaneDetector ld;

  logfile << "Opening Image: 'test.jpg' \n"; 
	
	Mat testmat = imread("../test/test.jpg", IMREAD_COLOR);  // load the sample image to test and compare

  logfile << "Retrieving the Image \n";
  logfile <<  "Image Specs: \n" <<
              "=========================" << endl << 
              "Is Empty:       " << testmat.empty() << endl << 
              "Dimensionality: " << testmat.dims << endl <<
              "Pixel Format:   " << testmat.depth() << endl <<
              "Size:           " << testmat.size << endl << endl;
                
  if(!testmat.size || testmat.empty()) passed = false;

  logfile << "Creating Empty Lane Array: Lanes Full of Zeros \n";

	array<Lane, 4> testlanes = { Lane({0, 0}), Lane({0, 0})}; 

  logfile << "Detecting Lanes: \n";
	
  uint32_t numlanes = LaneDetector::DetectLanes(testlanes, testmat);
  ld.DetectLanes(testmat);

  logfile << "Printing Lanes: \n";
  logfile << "Total Lanes Found: Static Call: " << numlanes 
                             << " Object Call: " << ld.GetNumLanes() << endl;

  cout << "Static Lanes: " << endl;
  for(Lane lane: testlanes) logfile << lane;

  cout << "Object Lanes: " << endl;
  for(Lane lane: ld.GetLanes()) logfile << lane;

  return passed;

}

bool Test::LIDARTest(){ return true; }

bool Test::GPSTest(){ return true; }


bool Test::SensorsTest(){ return true; }

bool Test::MotorTest(){ return true;}

bool Test::ObjectDetectionTest(){ return true; }

bool Test::RunAllTests(){
  
  bool senstest = SensorsTest();
  bool motortest = MotorTest();
  bool ldtest = LaneDetectionTest();
  bool odtest = ObjectDetectionTest();
  bool gpstest = GPSTest();
  bool lidartest = LIDARTest();
  bool camtest = CameraTest();

  cout << "Sensor Test: " << ((senstest)? "PASSED\n": "FAILED\n");
  cout << "Camera Test: " << ((camtest)? "PASSED\n": "FAILED\n") ;
  cout << "Motor Test: " << ((motortest)? "PASSED\n": "FAILED\n");
  cout << "GPS Test: " << ((gpstest)? "PASSED\n": "FAILED\n");
  cout << "LIDAR Test: " << ((lidartest)? "PASSED\n": "FAILED\n");
  cout << "Lane Detection Test: " << ((ldtest)? "PASSED\n": "FAILED\n");
  cout << "Object Detection Test: " << ((odtest)? "PASSED\n": "FAILED\n");

  return senstest && odtest && ldtest && motortest &&
    gpstest && lidartest && camtest;

}
