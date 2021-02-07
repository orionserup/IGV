#pragma once

#include <iostream>
#include <cmath>
#include <array>
#include "Camera.hpp"
#include "opencv2/opencv.hpp"
namespace igv{

struct Lane{

  double slope;
  int intercept;

  friend std::ostream& operator<<(std::ostream& os, const Lane& lane);

};

class LaneDetector{

public:

  LaneDetector(Camera& cam);

  static uint32_t DetectLanes(std::array<Lane, 2>& LaneArray, cv::Mat& image);
  uint32_t DetectLanes(cv::Mat& Image);
  bool isBusy(){ return busy; }
  std::array<Lane, 2>& GetLanes() { return lanes; }

private:

  bool busy;
  Camera cam;
  std::array<Lane, 2> lanes;

};
  
}


