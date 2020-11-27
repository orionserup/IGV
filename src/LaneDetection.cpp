#include "LaneDetection.hpp"

LaneDetector::LaneDetector(HardwareInterface& hal){
    this->hal = hal;
}

uint32_t LaneDetector::DetectLanes(vector<Lane>& LaneVector){
    
    this->hal.cam[USB].Capture();

    Mat myimage = *this->hal.cam[USB].GetImage();
    vector<Vec2f> linesP;

    Canny(InputArray(myimage), OutputArray(myimage), 50, 150);
    HoughLinesP(InputArray(myimage), OutputArray(myimage), 1, CV_PI/180, 50, 50, 10.0f);

    if(linesP.size() < 2) return 0; // if there is less than one line return 0 lanes

    double mag = 0;

    pair<double, uint32_t> largest[2] = {{0,0}, {0,0}};  // stores index and magnitiude of largest lines

    for( uint32_t i = 0; i < linesP.size(); i+=2){

        mag = linesP[i+i][0] - linesP[i][0] + linesP[i+1][1] - linesP[i][1];  // adds deltax and deltay

        if(mag > largest[0].first){
            largest[0].second = i;
            largest[0].first = mag;
        }
        else if(mag > largest[i].first){
            largest[1].second = i;
            largest[1].first = mag; 
        }

    }

    if(LaneVector.size() < 2) LaneVector.resize(2);

    double slope;
    int intercept;

    for( int i = 0; i < 2; i++){
        slope = (linesP[largest[i].second + 1][1] - linesP[largest[i].second][1])  // slope  = deltay/deltax
                / (linesP[largest[i].second + 1][0] - linesP[largest[i].second][0]);
        intercept = (uint32_t)(linesP[largest[1].second][1] - slope*linesP[largest[i].second][0]); // derived from point slope formula
        LaneVector[i] = {slope, intercept};  // fill in the lanes with their slopes and intercepts
    }

    return linesP.size()/2;

}