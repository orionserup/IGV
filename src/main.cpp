
#include "IGV.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;
using namespace igv;

int main(int argc, const char** argv){

    Mat testimage = imread("./test/test.png");

    cout << testimage.channels();

    array<Lane, 2> lanes = {(Lane){0.0f, 0}, (Lane){0.0f, 0}};

    uint32_t numlanes = DetectLanes(lanes, testimage);

    return numlanes;
}