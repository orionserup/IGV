/**
 * @file ObjectDetection.hpp
 * @author Orion Serup
 * @brief Contains all of the Prototypes and Classes for the Object Detection Functionality
 */

#pragma once

#include "main.hpp"
<<<<<<< HEAD
#include "Camera.hpp"
=======
>>>>>>> 72cc7470e803a47481bac4173ab46f32d84bf5a1

using namespace std;
using namespace cv;

namespace igv {

/** 
* @struct Object 
* @brief Holds Data about Objects 
*/
struct Object {

<<<<<<< HEAD
  Distance distance;
  Direction leftedge, rightedge;
  string classification;
=======
  Distance distance; //< distance to object
  Direction angle;   //< angle to the Object
  string classification; //< What type of object it is
>>>>>>> 72cc7470e803a47481bac4173ab46f32d84bf5a1

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
<<<<<<< HEAD
   * @brief Detects Objects and stores data in private members
   * 
   * @param Image 
   * @return void
=======
   * @fn DetectObjects
   * @brief Detects Objects in the given Image
   * @param Image Image to Detect Objects from
>>>>>>> 72cc7470e803a47481bac4173ab46f32d84bf5a1
   */
  void DetectObjects(Mat& Image);

  /**
<<<<<<< HEAD
   * @brief 
   * 
   * @param objs 
   * @param Image 
   * @return uint32_t 
   */
  static uint32_t DetectObjects(list<Object>& objs, Mat& Image);

  bool isBusy() { return this->busy; }

  uint32_t GetNumObjects() { return numobjects; }
  list<Object>& GetObjects() { return objects; }
=======
   * @fn DetectObjects
   * @brief Static Version of Object Detection Functionality
   * @param objs List of Objects to Fill with detected Objects
   * @param Image Image to Detect Objects From
   * @return uint32_t: Number of Objects Found 
   */
  static uint32_t DetectObjects(list<Object>& objs, Mat& Image);

  /**
   * @fn isBusy
   * @brief Returns if the Object Detector is Busy with an Operation
   * @return bool: if the Object is Busy
   */
  const bool isBusy() { return this->busy; }

  /**
   * @fn GetNumObjects
   * @brief Get the Number of Objects Found
   * @return uint32_t: Number of Objects Found
   */
  const uint32_t GetNumObjects() { return objects.size(); }

  /**
   * @fn GetObjects
   * @brief Returns a reference to a List Full of Objects
   * @return list<Object>&: List of Objects
   */
  list<Object>& GetObjects() const { return objects; }
>>>>>>> 72cc7470e803a47481bac4173ab46f32d84bf5a1

private:

  bool busy;
  list<Object> objects;

};

}
