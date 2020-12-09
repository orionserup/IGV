#include "test.hpp"
#include "opencv2/opencv.hpp"
#include "IGV.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;
using namespace igv;

bool CameraTest(ofstream& logfile);
bool MotorTest(ofstream& logfile);
bool LIDARTest(ofstream& logfile);
bool USTest(ofstream& logfile);
bool LaneDetectionTest(ofstream& logfile);
bool ObjectDetectionTest(ofstream& logfile);

void errorhandler(int errorcode);

int main(){

    ofstream logfile("test.log");

    if(logfile.is_open()) logfile << "Test Beginning \n";
    else{
        cout << "Cannot Open File 'test.log' \n";
        return 1;
    }
    
    cout << "HARDWARE TESTS: \n\n ";
    cout << "Camera Test:            " << CameraTest(logfile) ? "Passed \n": "Failed \n";
    cout << "Motor Test:             " << MotorTest(logfile) ? "Passed \n" : "Failed \n";
    cout << "LIDAR Test:             " << LIDARTest(logfile) ? "Passed \n" : "Failed \n";
    cout << "Ultrasonic Sensor Test: " << USTest(logfile) ? "Passed \n": "Failed \n";
    cout << "Object Detection Test:  " << ObjectDetectionTest(logfile) ? "Passed \n" : "Failed \n";

    return 0;
}

bool CameraTest(ofstream& logfile){

    bool Passed = true;

    logfile << "Creating USB Camera Object \n";
    HardwareInterface::Camera cam1(USB);

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

    logfile << "Creating Internal Camera Object \n";
    HardwareInterface::Camera cam2(INT);

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

bool MotorTest(ofstream& logfile){

}

bool LIDARTest(ofstream& logfile){

}

bool USTest(ofstream& logfile){

}

