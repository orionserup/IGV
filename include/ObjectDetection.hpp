/**
 * @file ObjectDetection.hpp
 * @author Orion Serup
 * @brief Contains all of the Prototypes and Classes for the Object Detection Functionality
 */

#pragma once

#include "main.hpp"
#include "Camera.hpp"

using namespace std;
using namespace cv;

namespace igv {

/** 
* @struct Object 
* @brief Holds Data about Objects 
*/
struct Object {

  Distance distance;
  Direction leftedge, rightedge;

};

/** 
* @fn operator<<(ostream& os, Object& obj)
* @brief Output Stream Operator to print Objects
* @param os Output Stream Object
* @param obj Object to Print Out
* @return ostream: Output Stream Object for Printing
*/
ostream& operator<<(ostream& os, Object& obj);

/**
 * @class ObjDetector
 * @brief Detects Objects 
 */
class ObjDetector{

public:

  /**
   * @brief Detects Objects and stores data in private members
   * 
   * @param Image 
   * @return void
   */
  void DetectObjects(Mat& ImageL, Mat& ImageR);
  
   /*
   * @fn DetectObjects
   * @brief Static Version of Object Detection Functionality
   * @param objs List of Objects to Fill with detected Objects
   * @param Image Image to Detect Objects From
   * @return uint32_t: Number of Objects Found 
   */
  static uint32_t DetectObjects(vector<Object>& objs, Mat& ImageL, Mat& ImageR);

  /**
   * @fn isBusy
   * @brief Returns if the Object Detector is Busy with an Operation
   * @return bool: if the Object is Busy
   */
  bool isBusy() { return this->busy; }

  /**
   * @fn GetNumObjects
   * @brief Get the Number of Objects Found
   * @return uint32_t: Number of Objects Found
   */
  uint32_t GetNumObjects() { return objects.size(); }

  /**
   * @fn GetObjects
   * @brief Returns a reference to a List Full of Objects
   * @return list<Object>&: List of Objects
   */
  vector<Object>& GetObjects() { return objects; }

private:

  bool busy;
  vector<Object> objects;

};

Direction PointToDirection(const cv::Point2f point);
Distance ColorToDistance(const uint8_t color);

}
