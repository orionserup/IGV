#pragma once

#include "main.hpp"

#include "Camera.hpp"

namespace igv{

struct Lane{

  double slope;
  int intercept;

  friend std::ostream& operator<<(std::ostream& os, const Lane& lane);

};

class LaneDetector{

public:

  static uint32_t DetectLanes(std::array<Lane, 2>& LaneArray, cv::Mat& image);
  uint32_t DetectLanes(cv::Mat& Image);
  bool isBusy(){ return busy; }
  std::array<Lane, 2>& GetLanes() { return lanes; }

private:

  bool busy;
  std::array<Lane, 2> lanes;

};
  
}


