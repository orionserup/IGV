/**
 * @file ObjectDetection.cpp
 * @author Orion Serup
 * @brief Contains all of the Object Detection Functionality Implementation
 * @bug None
 */

#include "ObjectDetection.hpp"

using namespace igv;
using namespace cv;

// Stream operator allows the lanes to be printed to file of stdout
ostream& igv::operator<<(ostream &os, Object &obj){

    os << "At Left Angle " << obj.leftedge << endl;
    os << "Until Right Angle" << obj.rightedge << endl;
    os << "With Distance " << obj.distance << endl;

    return os;
}

Direction igv::PointToDirection(const cv::Point2f point) {

    return (Direction)((double)FOV * (point.x - 0.5) / 2.0f); // 0.5 is the center so the angle is just the distance from the center times FOV/2

}

Distance igv::ColorToDistance(const uint8_t color) {

    return (FOCALLENGTH * CAMERADISTANCE) / color;
}

#ifndef CUDA // if not using the GPU

uint32_t ObjDetector::DetectObjects(vector<Object> &objects, Mat &imageL, Mat& imageR)
{

    Ptr<StereoBM> bm = StereoBM::create(15, 25);

    Mat diff, grayL, grayR;

    cvtColor(imageL, grayL, COLOR_RGB2GRAY);
    cvtColor(imageR, grayR, COLOR_RGB2GRAY);

    bm->compute(grayL, grayR, diff);

    SimpleBlobDetector::Params blobparams;

    blobparams.filterByColor = true;
    blobparams.minThreshold = 10.0f;
    blobparams.minArea = 20.0f;
    blobparams.blobColor = 255; 

    Ptr<SimpleBlobDetector> bd = SimpleBlobDetector::create(blobparams);

    std::vector<KeyPoint> kps;

    bd->detect(diff, kps);

    objects.resize(kps.size()); // resize to fit all of the objects

    for(uint8_t i = 0; i < objects.size(); i++) {

        Point2f leftedge;
        Point2f rightedge;

        leftedge.x = kps[i].pt.x - kps[i].size;
        rightedge.x = kps[i].pt.x + kps[i].size;

        objects[i].leftedge = PointToDirection(leftedge);
        objects[i].rightedge = PointToDirection(rightedge);

        objects[i].distance = ColorToDistance(diff.at<uint8_t>(kps[i].pt));

    }


    #ifdef DEBUG

    imshow("Disparity Map", diff);
    waitKey(0);
    
    #endif

    return objects.size();
}

void ObjDetector::DetectObjects(Mat& ImageL, Mat& ImageR)
{


    #ifdef DEBUG
    
    // Mat dest;

    // drawKeypoints(ImageL, keypoints[0], dest);
    // imshow("Key Points on Image", dest);
    // waitKey(0);

    #endif

}

#else

uint32_t ObjDetector::DetectObjects(list<Object> &objs, Mat &Image)
{

    return objs.size();
}

uint32_t ObjDetector::DetectObjects(Mat &Image)
{

    busy = true;

    busy = false;

    return objs.size();
}

#endif

