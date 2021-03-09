#pragma once

#include "main.hpp"
#include "Camera.hpp"

namespace igv{

struct Lane{

  double slope;
  int intercept;

};

std::ostream& operator<<(std::ostream& os, Lane& lane);

class LaneDetector{

public:

  static uint32_t DetectLanes(std::array<Lane, 4>& LaneArray, cv::Mat& image);
  void DetectLanes(cv::Mat& Image);
  uint32_t GetNumLanes() { return numlanes; }
  bool isBusy(){ return busy; }
  std::array<Lane, 4>& GetLanes() { return lanes; }

private:

  bool busy;
  std::array<Lane, 4> lanes;
  uint32_t numlanes;

};
  
}


