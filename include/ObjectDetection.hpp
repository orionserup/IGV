#pragma once

#include "main.hpp"

#include "Camera.hpp"

using namespace std;
using namespace cv;

/*!
* \namespace igv
* \brief Namespace for the Project
*/
namespace igv {

/*!
* \struct Object
* \brief Holds Data about Objects 
*/
struct Object {

  Distance distance;
  Direction angle;
  string classification;

};

/*!
* \fn operator<<(ostream& os, Object& obj)
* \brief Output Stream Operator to print Objects
* \param os Output Stream Object
* \param obj Object to Print Out
* \return ostream& 
*/
ostream& operator<<(ostream& os, Object& obj);

class ObjDetector{

public:

  uint32_t DetectObjects(Mat& Image);
  static uint32_t DetectObjects(list<Object>& objs, Mat& Image);
  bool isBusy() { return this->busy; }
  uint32_t GetNumObjects() { return numobjects; }
  list<Object>& GetObjects() { return objects; }

private:

  bool busy;
  uint32_t numobjects;
  list<Object> objects;

};

}
