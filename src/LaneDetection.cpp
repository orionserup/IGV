#include "LaneDetection.hpp"

using namespace igv;
using namespace std;
using namespace cv;

// Stream operator overload, allows you to print Lanes
ostream& igv::operator<<(ostream& os, Lane& lane){
    
    os << "Lane Slope: " << lane.slope << endl;
    os << (lane.slope == 0.0f? " Y-Intercept: " : " X-Intercept: ");
    os << lane.intercept << endl;

    return os;
}

#ifndef CUDA  // if not using the GPU

/* Lane Detection Function:
 * 
 * Reads an image and finds the largest Lanes and fills an array with the 2 largest
 * @param: LaneArray: a preexisting array full of lanes that gets modified by the function
 * @param: image: a preexisting matrix representing an image that gets read for lanes
 * @retval: returns the number of lanes detected total
 * 
 */

uint32_t LaneDetector::DetectLanes(array<Lane, 2>& LaneArray, Mat& image){

    Mat gray, edged;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    Canny(gray, edged, 50, 200);

    vector<Vec4i> linesP;  // a vector to fill with line points
    HoughLinesP(gray, linesP, 3, CV_PI/256, 25);  // find the lines

    if(linesP.size() < 2) return 0; // if there is less than one line return 0 lanes
    
    // store index and magnitiude of largest lines and a temporary magnitude
    struct linedata{
    
      double mag;
      uint32_t index;
    
    } largest[2] = {{0.0f,0}, {0.0f,0}};

    double mag;
    
    for( uint32_t i = 0; i < linesP.size(); i++){  // find the two largest lines

        mag = linesP[i][X1] - linesP[i][X0] + linesP[i][Y1] - linesP[i][Y0];  

        if(mag > largest[0].mag) 
            largest[0] = {mag, i}; // if larger than the largest then replace it
        else if(mag > largest[1].mag) 
            largest[1] = {mag, i}; // same here except second largest
    }

    double slope; // temporary slope value
    int intercept; // temporary intercept value

    for(uint32_t i = 0; i < 2; i++){  // put the two biggest lines in the Lane Vector 

        if(linesP[largest[i].index][X0] == linesP[largest[i].index][X1]){ // horizontal 
            
            slope = DBL_MAX;
            intercept = linesP[largest[i].index][X0];
        }
        else if(linesP[largest[i].index][Y0] == linesP[largest[i].index][Y1]){ // vertical

            slope = 0.0f;
            intercept = linesP[largest[i].index][Y0];
        }
        else{
        // m = deltay/deltax
        slope = (linesP[largest[i].index][Y1] - linesP[largest[i].index][Y0]) 
                    / (linesP[largest[i].index][X1] - linesP[largest[i].index][X0]);
        // b = Yo - mXo
        intercept = (linesP[largest[i].index][Y0] - slope*linesP[largest[i].index][X0]); 
        }

        LaneArray[i] = { slope, intercept };

        #ifdef DEBUG // if debugging then print the image with lines

        line(image, Point(linesP[largest[i].index][X0], linesP[largest[i].index][Y0]), 
                    Point(linesP[largest[i].index][X1], linesP[largest[i].index][Y1]), Scalar(0, 0, 255));
        imshow("Lane Detected Image", image);

        #endif

    }

    return linesP.size();  // return how many lines are seen
}

// same things but not static

void LaneDetector::DetectLanes(Mat& image){

    busy = true;

    Mat gray, edged;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    Canny(gray, edged, 50, 255);

    vector<Vec4i> linesP;  // a vector to fill with line points
    HoughLinesP(edged, linesP, 3, CV_PI/256, 50);  // find the lines

    if(!linesP.size()){
        this->numlanes = 0;
        return; // if there is less than one line return 0 lanes
    }
    // store index and magnitiude of largest lines and a temporary magnitude
    struct linedata{
    
      double mag;
      uint32_t index;
    
    } largest[2] = {{0.0f,0}, {0.0f,0}};

    double mag;
    
    for( uint32_t i = 0; i < linesP.size(); i++){  // find the two largest lines

        mag = linesP[i][X1] - linesP[i][X0] + linesP[i][Y1] - linesP[i][Y0];  

        if(mag > largest[0].mag) 
            largest[0] = {mag, i}; // if larger than the largest then replace it
        else if(mag > largest[1].mag) 
            largest[1] = {mag, i}; // same here except second largest
    }

    double slope; // temporary slope value
    int intercept; // temporary intercept value

    for(uint32_t i = 0; i < 2; i++){  // put the two biggest lines in the Lane Vector 

        if(linesP[largest[i].index][X0] == linesP[largest[i].index][X1]){ // horizontal 
            
            slope = DBL_MAX;
            intercept = linesP[largest[i].index][X0];
        }
        else if(linesP[largest[i].index][Y0] == linesP[largest[i].index][Y1]){ // vertical

            slope = 0.0f;
            intercept = linesP[largest[i].index][Y0];
        }
        else{
        // m = deltay/deltax
        slope = (linesP[largest[i].index][Y1] - linesP[largest[i].index][Y0]) 
                    / (linesP[largest[i].index][X1] - linesP[largest[i].index][X0]);
        // b = Yo - mXo
        intercept = (linesP[largest[i].index][Y0] - slope*linesP[largest[i].index][X0]); 
        }

        this->lanes[i] = { slope, intercept };

        #ifdef DEBUG // if debugging then print the image with lines

        line(image, Point(linesP[largest[i].index][X0], linesP[largest[i].index][Y0]),
                    Point(linesP[largest[i].index][X1], linesP[largest[i].index][Y1]), Scalar(0, 0, 255));
        imshow("Lane Detected Image", image);

        #endif

    }

    busy = false;
    this->numlanes = linesP.size();  // return how many lines are seen

}

#else // if we are using the GPU

// Same Algorithm but using GPU

uint32_t LaneDetector::DetectLanes(array<Lane, 2>& lanes, Mat& image){

    busy = true;

    GpuMat img, edge, lines;
    vector<uint32_t> votes;
    vector<Vec2f> linesP;

    uint32_t best[2] = {0};
    uint32_t index[2];

    img.upload(image);

    gpu::cvtColor(img, img, COLOR_BGR2GRAY);
    gpu::Canny(img, edge, 50, 200);

    gpu::HoughLines(edge, lines, 1,  CV_PI/128, 10);
    gpu::HoughLinesDownload(lines, linesP, votes);

    if(!linesP.size()) return 0;

    for(uint32_t i = 0; i < linesP.size(), i++){
        
        if(votes[i] > best[0]){
            best[0] = votes[i];
            index[0] = i;
        }
        else if(votes[i] > best[1]){
            best[1] = votes[i];
            index[1] = i;
        }
    }

    double slope;
    int intercept;

    for(uint32_t i = 0; i < 2; i++){

        slope = tan(CV_PI/2 - linesP[index[i]][1]); // y/x = tan(theta)
        if(linesP[index[i]][1] == || linesP[index[i][1]] == CV_PI/2) 
            intercept = linesP[index[i][0]];  // if slope is 0 or inf, intercept is rho
        else intercept = -1*slope*linesP[index[i]][0]/cos(linesP[index[i]][1]);

        lanes[i] = { slope, intercept };

        #ifdef

        



        #endif

    }

    this->numlanes = linesP.size();
    busy = false;

}


void LaneDetector::DetectLanes(Mat& image){

    busy = true;

    GpuMat img, edge, lines;
    vector<uint32_t> votes;
    vector<Vec2f> linesP;

    uint32_t best[2] = {0};
    uint32_t index[2];

    img.upload(image);

    gpu::cvtColor(img, img, COLOR_BGR2GRAY);
    gpu::Canny(img, edge, 50, 200);

    gpu::HoughLines(edge, lines, 1,  CV_PI/128, 10);
    gpu::HoughLinesDownload(lines, linesP, votes);

    if(!linesP.size()){
        this->numlanes = 0;
        return;
    }

    for(uint32_t i = 0; i < linesP.size(), i++){
        
        if(votes[i] > best[0]){
            best[0] = votes[i];
            index[0] = i;
        }
        else if(votes[i] > best[1]){
            best[1] = votes[i];
            index[1] = i;
        }
    }

    double slope;
    int intercept;

    for(uint32_t i = 0; i < 2; i++){

        slope = tan(CV_PI/2 - linesP[index[i]][1]); // y/x = tan(theta)
        if(linesP[index[i]][1] == || linesP[index[i][1]] == CV_PI/2) 
            intercept = linesP[index[i][0]];  // if slope is 0 or inf, intercept is rho
        else intercept = -1*slope*linesP[index[i]][0]/cos(linesP[index[i]][1]);

        lanes[i] = { slope, intercept };

        #ifdef DEBUG

        



        #endif

    }

    this->numlanes = linesP.size();
    busy = false;

}

#endif
