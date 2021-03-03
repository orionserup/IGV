#pragma once

#include "main.hpp"

#include "Camera.hpp"

namespace igv{

struct Lane{

  double slope;
  int intercept;

  friend std::ostream& operator<<(std::ostream& os, Lane& lane);

};

class LaneDetector{

public:

  static uint32_t DetectLanes(std::array<Lane, 2>& LaneArray, cv::Mat& image);
  void DetectLanes(cv::Mat& Image);
  uint32_t GetNumLanes() { return numlanes; }
  bool isBusy(){ return busy; }
  Lane GetLane(LaneNum num) { return lanes[num]; }

private:

  bool busy;
  std::array<Lane, 2> lanes;
  uint32_t numlanes;

};
  
}


