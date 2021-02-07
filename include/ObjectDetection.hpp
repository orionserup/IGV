#pragma once

#include "Defines.hpp"

#include "opencv2/opencv.hpp"
#include "Camera.hpp"
#include <vector>

using namespace std;
using namespace cv;

namespace igv {

struct Object {

  double distance;
  Direction angle;
  string classification;

  friend ostream& operator<<(ostream& os, Object& obj);

};
class ObjDetector{

public:
  
  ObjDetector(Camera& cam);

  uint32_t DetectObjects(Mat& Image);
  static uint32_t DetectObjects(vector<Object>& objs, Mat& Image);
  bool isBusy() { return this->busy; }
  vector<Object>& GetObjects() { return objects; }

private:

  bool busy;
  vector<Object> objects;
  Camera cam;

};

}
