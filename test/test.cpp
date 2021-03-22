
#include "test.hpp"

using namespace std;
using namespace cv;
using namespace igv;

Test::Test(const char *logfile) : logfile(logfile) {}

Test::~Test() { logfile.close(); }

bool Test::CameraTest()
{

        if (Ready())
        {

                bool Passed = true;
                auto begin = chrono::system_clock::now();

                logfile << "Creating Lane Camera Object \n";
                Camera cam1(LANECAMPORT);

                logfile << "Taking a Picture \n";
                cam1.Capture();

                logfile << "Retrieving the Image \n";
                Mat testimage = cam1.GetImage();

                logfile << "Image Specs: \n"
                        << "========================="
                        << "Is Empty:       " << testimage.empty() << endl
                        << "Dimensionality: " << testimage.dims << endl
                        << "Pixel Format:   " << testimage.depth() << endl
                        << "Size:           " << testimage.size << endl
                        << endl;

                if (testimage.empty() || !testimage.size)
                        Passed = false;

                logfile << "Creating Object Camera Object \n";
                Camera cam2(OBJCAMPORT);

                logfile << "Taking a Picture: \n";
                cam2.Capture();

                logfile << "Retrieving the Image " << endl
                        << "Image Specs: " << endl
                        << "========================="
                        << "Is Empty:       " << testimage.empty() << endl
                        << "Dimensionality: " << testimage.dims << endl
                        << "Pixel Format:   " << testimage.depth() << endl
                        << "Size:           " << testimage.size << endl
                        << endl;

                if (testimage.empty() || !testimage.size)
                        Passed = false;

                auto end = chrono::system_clock::now();

                chrono::nanoseconds time = end - begin;

                logfile << "Camera Test: " << (Passed ? "PASSED" : "FAILED") << endl;
                logfile << "Test Completed in " << time.count() << "ns" << endl;

                return Passed;
        }

        return false;
}

bool Test::LaneDetectionTest(string filename)
{

        if (Ready())
        {

                bool passed = true;

                LaneDetector ld;

                logfile << "Opening Image: " << filename << endl;
                Mat testmat = imread(filename); // load the sample image to test and compare

                logfile << "Retrieving the Image" << endl
                        << "Image Specs: " << endl
                        << "=========================" << endl
                        << "Is Empty:       " << testmat.empty() << endl
                        << "Dimensionality: " << testmat.dims << endl
                        << "Pixel Format:   " << testmat.depth() << endl
                        << "Size:           " << testmat.size << endl
                        << endl;

                if (!testmat.size || testmat.empty())
                        passed = false;

                logfile << "Creating Empty Lane Array: Lanes Full of Zeros \n";
                array<Lane, 4> testlanes = {0};

                logfile << "Detecting Lanes: \n";

                auto staticbegin = chrono::system_clock::now();
                uint32_t numlanes = LaneDetector::DetectLanes(testlanes, testmat);
                chrono::nanoseconds statictime = chrono::system_clock::now() - staticbegin;

                auto begin = chrono::system_clock::now();
                ld.DetectLanes(testmat);
                chrono::nanoseconds time = chrono::system_clock::now() - begin;

                logfile << "Printing Lanes: " << endl
                        << "Total Lanes Found:" << endl
                        << "Static Call: " << numlanes
                        << "Object Call: " << ld.GetNumLanes() << endl
                        << endl
                        << "Time Taken For Tests: " << endl
                        << "Static Time: " << statictime.count() << "ns" << endl
                        << "Object Time: " << time.count() << "ns" << endl
                        << endl;

                logfile << "Static Lanes: " << endl;
                for (Lane lane : testlanes)
                        logfile << lane;

                logfile << "Object Lanes: " << endl;
                for (Lane lane : ld.GetLanes())
                        logfile << lane;

                return passed;
        }

        return false;
}

bool Test::LIDARTest() { return true; }

bool Test::GPSTest() { return true; }

bool Test::SensorsTest() { return true; }

bool Test::MotorTest() { return true; }

bool Test::ObjectDetectionTest() { return true; }

bool Test::Ready() { return logfile.is_open(); }

bool Test::RunAllTests()
{

        bool senstest = SensorsTest();
        bool motortest = MotorTest();
        bool ldtest = LaneDetectionTest("../test/test.jpeg");
        bool odtest = ObjectDetectionTest();
        bool gpstest = GPSTest();
        bool lidartest = LIDARTest();
        bool camtest = CameraTest();

        cout << "Sensor Test: " << ((senstest) ? "PASSED\n" : "FAILED\n");
        cout << "Camera Test: " << ((camtest) ? "PASSED\n" : "FAILED\n");
        cout << "Motor Test: " << ((motortest) ? "PASSED\n" : "FAILED\n");
        cout << "GPS Test: " << ((gpstest) ? "PASSED\n" : "FAILED\n");
        cout << "LIDAR Test: " << ((lidartest) ? "PASSED\n" : "FAILED\n");
        cout << "Lane Detection Test: " << ((ldtest) ? "PASSED\n" : "FAILED\n");
        cout << "Object Detection Test: " << ((odtest) ? "PASSED\n" : "FAILED\n");

        return senstest && odtest && ldtest && motortest &&
               gpstest && lidartest && camtest;
}
