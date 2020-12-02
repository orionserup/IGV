#include "LaneDetection.hpp"

LaneDetector::LaneDetector(HardwareInterface& hal): hal(hal){}

uint32_t LaneDetector::DetectLanes(array<Lane, 2>& LaneArray){
    
    hal.LaneCam.Capture(); // take a picture

    Mat myimage = hal.LaneCam.GetImage();  // get a copy of the image

    vector<Vec2f> linesP;  // a vector to fill with line points

    Canny(InputArray(myimage), OutputArray(myimage), 50, 150); // use edge detection
    HoughLinesP(InputArray(myimage), OutputArray(myimage), 1, CV_PI/180, 50, 50, 10.0f);  // find the lines

    if(linesP.size() < 2) return 0; // if there is less than one line return 0 lanes

    double mag = 0;  // magnitude of the lines storage

    pair<double, uint32_t> largest[2] = {{0,0}, {0,0}};  // stores index and magnitiude of largest lines

    for( uint32_t i = 0; i < linesP.size(); i+=2){  // find the two largest lines

        mag = linesP[i+i][x] - linesP[i][x] + linesP[i+1][y] - linesP[i][y];  // adds deltax and deltay

        if(mag > largest[0].first) largest[0] = {mag, i}; // if larger than the largest then replace it
        else if(mag > largest[i].first) largest[1] = {mag, i};  // same here except second largest

    }

    double slope;
    int intercept;

    for( int i = 0; i < 2; i++){  // put the two biggest lines in the Lane Vector

        if(linesP[largest[i].second][x] == linesP[largest[i].second + 1][x]){ // if horizontal lines then slope = max double and intercept is least int 
            
            slope = DBL_MAX;
            intercept = INT32_MIN;

        }
        else{

        slope = (linesP[largest[i].second + 1][y] - linesP[largest[i].second][y])  // slope  = deltay/deltax
                / (linesP[largest[i].second + 1][x] - linesP[largest[i].second][x]);
        intercept = (int)(linesP[largest[1].second][y] - slope*linesP[largest[i].second][x]); // derived from point slope formula

        }
        
        LaneArray[i] = { slope, intercept };  // fill in the lanes with their slopes and intercepts
    }

    return linesP.size()/2;  // return how many lines are seen

}