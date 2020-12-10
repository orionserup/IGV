
#include "IGV.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;
using namespace igv;

int main(int argc, const char** argv){

    string path = samples::findFile("../test/test.jpg");

    Mat testimage = imread(path, IMREAD_COLOR);

    Mat gray, canny;

    cvtColor(testimage, gray, COLOR_BGR2GRAY);
    Canny(gray, canny, 10.0f, 150.0f);

    imshow("Canny", canny);

    array<Lane, 2> lanes = {(Lane){0.0f, 0}, (Lane){0.0f, 0}};

    uint32_t numlanes = DetectLanes(lanes, testimage);

    return numlanes;
}