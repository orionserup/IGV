#include "LaneDetection.hpp"

#define x 0
#define y 1

using namespace igv;

// Stream operator overload, allows you to print Lanes
ostream& operator<<(ostream& os, const Lane& lane){
    
    os << "Slope: " << lane.slope << endl;
    os << (lane.slope == 0.0f? " Y-Intercept: " : " X-Intercept: ");
    os << lane.intercept << endl;

    return os;
}

/* Lane Detection Function:
 * 
 * Reads an image and finds the largest Lanes and fills an array with the 2 largest
 * @param: LaneArray: a preexisting array full of lanes that gets modified by the function
 * @param: image: a preexisting matrix representing an image that gets read for lanes
 * @retval: returns the number of lanes detected total
 * 
 */

uint32_t DetectLanes(array<Lane, 2>& LaneArray, Mat& image){

    vector<Vec2f> linesP;  // a vector to fill with line points
    HoughLinesP(image, linesP, 1, CV_PI/256, 50, 25, 10.0f);  // find the lines

    if(linesP.size() < 2) return 0; // if there is less than one line return 0 lanes
    
    // store index and magnitiude of largest lines and a temporary magnitude
    struct linedata{
    
      double mag;
      uint32_t index;
    
    } largest[2] = {{0.0f,0}, {0.0f,0}};

    double mag;
    
    for( uint32_t i = 0; i < linesP.size(); i+=2){  // find the two largest lines

        mag = linesP[i+i][x] - linesP[i][x] + linesP[i+1][y] - linesP[i][y];  

        if(mag > largest[0].mag) 
            largest[0] = {mag, i}; // if larger than the largest then replace it
        else if(mag > largest[1].mag) 
            largest[1] = {mag, i}; // same here except second largest
    }

    double slope; // temporary slope value
    int intercept; // temporary intercept value

    for(uint32_t i = 0; i < 2; i++){  // put the two biggest lines in the Lane Vector 

        if(linesP[largest[i].index][x] == linesP[largest[i].index + 1][x]){ // horizontal 
            
            slope = DBL_MAX;
            intercept = linesP[largest[i].index][x];
        }
        else if(linesP[largest[i].index][y] == linesP[largest[i].index + 1][y]){ // vertical

            slope = 0.0f;
            intercept = linesP[largest[i].index][y];
        }
        else{
        // m = deltay/deltax
        slope = (linesP[largest[i].index + 1][y] - linesP[largest[i].index][y]) 
                    / (linesP[largest[i].index + 1][x] - linesP[largest[i].index][x]);
        // b = Yo - mXo
        intercept = (int)(linesP[largest[i].index][x] - slope*linesP[largest[i].index][x]); 
        }

        LaneArray[i].slope = slope;
        LaneArray[i].intercept = intercept;
    }

    return linesP.size()/2;  // return how many lines are seen
}
