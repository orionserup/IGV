#include "LaneDetection.hpp"

ostream& operator<<(ostream& os, const igv::Lane& lane){
    
    os << "Slope: " << lane.slope;
    os << (lane.slope == 0.0f) ? " Y-Intercept: " : " X-Intercept: ";
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

uint32_t igv::DetectLanes(array<igv::Lane, 2>& LaneArray, Mat& image){

    vector<Vec2f> linesP;  // a vector to fill with line points

    HoughLinesP(image, linesP, 1, CV_PI/256, 50, 25, 10.0f);  // find the lines

    if(linesP.size() < 2) return 0; // if there is less than one line return 0 lanes

    double mag = 0;  // magnitude of the lines storage

    pair<double, uint32_t> largest[2] = {{0,0}, {0,0}};  // stores index and magnitiude of largest lines

    for( uint32_t i = 0; i < linesP.size(); i+=2){  // find the two largest lines

        mag = linesP[i+i][x] - linesP[i][x] + linesP[i+1][y] - linesP[i][y];  // adds deltax and deltay

        if(mag > largest[0].first) largest[0] = {mag, i}; // if larger than the largest then replace it
        else if(mag > largest[i].first) largest[1] = {mag, i};  // same here except second largest

    }

    double slope;
    uint32_t intercept;

    for( int i = 0; i < 2; i++){  // put the two biggest lines in the Lane Vector

        if(linesP[largest[i].second][x] == linesP[largest[i].second + 1][x]){ // if vertical slope is max and xintercept is xintercpt 
            
            slope = DBL_MAX;
            intercept = linesP[largest[i].second][x];

        }
        else if(linesP[largest[i].second][y] == linesP[largest[i].second][y]){

            slope = 0.0f;
            intercept = linesP[largest[i].second][y];
        }
        else{

        slope = (linesP[largest[i].second + 1][y] - linesP[largest[i].second][y])  // slope  = deltay/deltax
                / (linesP[largest[i].second + 1][x] - linesP[largest[i].second][x]);
        intercept = (uint32_t)(linesP[largest[1].second][x] - linesP[largest[i].second][x]/slope); // derived from point slope formula

        }
        
        LaneArray[i] = { slope, intercept };  // fill in the lanes with their slopes and intercepts
    }

    return linesP.size()/2;  // return how many lines are seen

}