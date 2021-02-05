#include "LaneDetection.hpp"
#include <cmath>

#define x0 0
#define y0 1
#define x1 2
#define y1 3

using namespace igv;

// Stream operator overload, allows you to print Lanes
ostream& operator<<(ostream& os, const Lane& lane){
    
    os << "Slope: " << lane.slope << endl;
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

uint32_t DetectLanes(array<Lane, 2>& LaneArray, Mat& image){

    Mat gray, edged;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    Canny(gray, edged, 50, 200);

    vector<Vec4i> linesP;  // a vector to fill with line points
    HoughLinesP(gray, linesP, 1, CV_PI/256, 50, 25, 10.0f);  // find the lines

    if(linesP.size() < 2) return 0; // if there is less than one line return 0 lanes
    
    // store index and magnitiude of largest lines and a temporary magnitude
    struct linedata{
    
      double mag;
      uint32_t index;
    
    } largest[2] = {{0.0f,0}, {0.0f,0}};

    double mag;
    
    for( uint32_t i = 0; i < linesP.size(); i++){  // find the two largest lines

        mag = linesP[i][x1] - linesP[i][x0] + linesP[i][y1] - linesP[i][y0];  

        if(mag > largest[0].mag) 
            largest[0] = {mag, i}; // if larger than the largest then replace it
        else if(mag > largest[1].mag) 
            largest[1] = {mag, i}; // same here except second largest
    }

    double slope; // temporary slope value
    int intercept; // temporary intercept value

    for(uint32_t i = 0; i < 2; i++){  // put the two biggest lines in the Lane Vector 

        if(linesP[largest[i].index][x0] == linesP[largest[i].index][x1]){ // horizontal 
            
            slope = DBL_MAX;
            intercept = linesP[largest[i].index][x0];
        }
        else if(linesP[largest[i].index][y0] == linesP[largest[i].index][y1]){ // vertical

            slope = 0.0f;
            intercept = linesP[largest[i].index][y0];
        }
        else{
        // m = deltay/deltax
        slope = (linesP[largest[i].index][y1] - linesP[largest[i].index][y0]) 
                    / (linesP[largest[i].index][x1] - linesP[largest[i].index][x0]);
        // b = Yo - mXo
        intercept = (linesP[largest[i].index][y0] - slope*linesP[largest[i].index][x0]); 
        }

        LaneArray[i] = { slope, intercept };

        #ifdef DEBUG // if debugging then print the image with lines

        line(image, Point(linesP[largest[0].index][x0], Point(lines)), Scalar(0, 0, 255));
        imshow(image);

        #endif

    }

    return linesP.size();  // return how many lines are seen
}

#else

uint32_t DetectLanes(array<Lane, 2>& lanes, Mat& image){

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
    uint32_t intercept;

    for(uint32_t i = 0; i < 2; i++){

        slope = tan(CV_PI/2 - linesP[index[i]][1]); // y/x = tan(theta)
        if(linesP[index[i]][1] == || linesP[index[i][1]] == CV_PI/2) 
            intercept = linesP[index[i][0]];  // if slope is 0 or inf, intercept is rho
        else intercept = -1*slope*linesP[index[i]][0]/cos(linesP[index[i]][1]);

        lanes[i] = { slope, intercept };

        #ifdef

        



        #endif

    }

    return linesP.size();

}





#endif