/**
 * @file LaneDetection.cpp
 * @author Orion Serup
 * @brief  Contains the Lane Detection Functionality Implementation
 * @bug None
 */

#include "LaneDetection.hpp"

using namespace igv;
using namespace std;
using namespace cv;

/**
 * @brief
 * @note
 * @param  &os:
 * @param  &lane:
 * @retval
 */
ostream &igv::operator<<(ostream &os, Lane &lane) {

  os << "Lane Slope: " << lane.slope << endl;
  os << (lane.slope == 0.0f ? " Y-Intercept: " : " X-Intercept: ");
  os << lane.intercept << endl;

  return os;
}

#ifndef CUDA // if not using the GPU

/** Lane Detection Function:
 *
 * Reads an image and finds the largest Lanes and fills an array with the 4
 * largest
 * @param LaneArray: a preexisting array full of lanes that gets modified by the
 * function
 * @param image: a preexisting matrix representing an image that gets read for
 * lanes
 * @returns uint32_t
 *
 */
uint32_t LaneDetector::DetectLanes(array<Lane, 4> &LaneArray, Mat &image) {

#ifdef DEBUG
  Mat imgcopy;
  image.copyTo(imgcopy);
#endif

  Mat gray;
  Mat edged;

  cvtColor(image, gray, COLOR_BGR2GRAY);
  Canny(gray, edged, 200, 200);

  vector<Vec4i> linesP; // a vector to fill with line points
  HoughLinesP(edged, linesP, 1, CV_PI / 256, 80, 80, 10); // find the lines

  if (linesP.size() < 1)
    return 0; // if there is less than one line return 0 lanes

  // store index and magnitiude of largest lines and a temporary magnitude
  struct linedata {

    double mag;
    uint32_t index;

  } largest[4] = {{0.0f, 0}, {0.0f, 0}, {0.0f, 0}, {0.0f, 0}};

  double mag;

  for (uint32_t i = 0; i < linesP.size(); i++) { // find the two largest lines

    mag = linesP[i][X1] - linesP[i][X0] + linesP[i][Y1] - linesP[i][Y0];

    if (mag > largest[0].mag)
      largest[0] = {mag, i}; // if larger than the largest then replace it
    else if (mag > largest[1].mag)
      largest[1] = {mag, i}; // same here except second largest
    else if (mag > largest[2].mag)
      largest[2] = {mag, i};
    else if (mag > largest[3].mag)
      largest[3] = {mag, i};
  }

  double slope;  // temporary slope value
  int intercept; // temporary intercept value

  for (uint32_t i = 0; i < 4 && i < linesP.size();
       i++) { // put the two biggest lines in the Lane Vector

    if (linesP[largest[i].index][X0] ==
        linesP[largest[i].index][X1]) { // horizontal

      slope = DBL_MAX;
      intercept = linesP[largest[i].index][X0];
    } else if (linesP[largest[i].index][Y0] ==
               linesP[largest[i].index][Y1]) { // vertical

      slope = 0.0f;
      intercept = linesP[largest[i].index][Y0];
    } else {
      // m = deltay/deltax
      slope = (linesP[largest[i].index][Y1] - linesP[largest[i].index][Y0]) /
              (linesP[largest[i].index][X1] - linesP[largest[i].index][X0]);
      // b = Yo - mXo
      intercept =
          (linesP[largest[i].index][Y0] - slope * linesP[largest[i].index][X0]);
    }

    LaneArray[i].slope = slope;
    LaneArray[i].intercept = intercept;

#ifdef DEBUG // if debugging then print the image with lines

    line(imgcopy,
         Point(linesP[largest[i].index][X0], linesP[largest[i].index][Y0]),
         Point(linesP[largest[i].index][X1], linesP[largest[i].index][Y1]),
         Scalar(0, 0, 255));

#endif
  }

#ifdef DEBUG
  imwrite("../test/StaticLDed.png", imgcopy);
#endif

  return linesP.size(); // return how many lines are seen
}

// same things but not static
/**
 * @brief
 *
 * @param image
 */
void LaneDetector::DetectLanes(Mat &image) {

  busy = true;

#ifdef DEBUG
  Mat imgcopy;
  image.copyTo(imgcopy);
#endif

  Mat gray, edged;
  cvtColor(image, gray, COLOR_BGR2GRAY);
  Canny(gray, edged, 190, 190);

  vector<Vec4i> linesP; // a vector to fill with line points
  HoughLinesP(edged, linesP, 1, CV_PI / 512.0f, 1, 50, 0); // find the lines

  if (!linesP.size()) {
    this->numlanes = 0;
    return; // if there is less than one line return 0 lanes
  }
  // store index and magnitiude of largest lines and a temporary magnitude
  struct linedata {
    double mag;
    uint32_t index;

  } largest[4] = {{0.0f, 0}, {0.0f, 0}, {0.0f, 0}, {0.0f, 0}};

  double mag;

  for (uint32_t i = 0; i < linesP.size(); i++) { // find the two largest lines

    mag = linesP[i][X1] - linesP[i][X0] + linesP[i][Y1] - linesP[i][Y0];

    if (mag > largest[0].mag)
      largest[0] = {mag, i}; // if larger than the largest then replace it

    else if (mag > largest[1].mag)
      largest[1] = {mag, i}; // same here except second largest

    else if (mag > largest[2].mag)
      largest[2] = {mag, i};

    else if (mag > largest[3].mag)
      largest[3] = {mag, i};
  }

  double slope;  // temporary slope value
  int intercept; // temporary intercept value

  for (uint32_t i = 0; i < 4 && i < linesP.size();
       i++) { // put the two biggest lines in the Lane Vector

    if (linesP[largest[i].index][X0] ==
        linesP[largest[i].index][X1]) { // horizontal

      slope = DBL_MAX;
      intercept = linesP[largest[i].index][X0];
    } else if (linesP[largest[i].index][Y0] ==
               linesP[largest[i].index][Y1]) { // vertical

      slope = 0.0f;
      intercept = linesP[largest[i].index][Y0];
    } else {
      // m = deltay/deltax
      slope =
          (float)(linesP[largest[i].index][Y1] - linesP[largest[i].index][Y0]) /
          (float)(linesP[largest[i].index][X1] - linesP[largest[i].index][X0]);
      // b = Yo - mXo
      intercept =
          (linesP[largest[i].index][Y0] - slope * linesP[largest[i].index][X0]);
    }

    this->lanes[i] = (Lane){slope, intercept};

#ifdef DEBUG // if debugging then print the image with lines

    line(imgcopy,
         Point(linesP[largest[i].index][X0], linesP[largest[i].index][Y0]),
         Point(linesP[largest[i].index][X1], linesP[largest[i].index][Y1]),
         Scalar(0, 0, 255));

#endif
  }

#ifdef DEBUG

  imshow("Canny", edged);
  waitKey(0);

  imshow("LDed", imgcopy);
  waitKey(0);

  imwrite("LDed.png", imgcopy);

#endif

  busy = false;
  this->numlanes = linesP.size(); // return how many lines are seen
}

#else // if we are using the GPU

// Same Algorithm but using GPU

uint32_t LaneDetector::DetectLanes(array<Lane, 4> &lanes, Mat &image) {

  cuda::GpuMat img(LANECAMWIDTH, LANECAMWIDTH, CV_8UC1);
  cuda::GpuMat gray(LANECAMWIDTH, LANECAMHEIGHT, CV_8UC1);

  cuda::GpuMat lanes;

#ifdef

#endif
}
}

void LaneDetector::DetectLanes(Mat &image) {

  busy = true;

  GpuMat img, edge, lines;
  vector<uint32_t> votes;
  vector<Vec2f> linesP;

  uint32_t best[2] = {0};
  uint32_t index[2];

  img.upload(image);

  cuda::cvtColor(img, gray, COLOR_BGR2GRAY);
  cuda::Canny(gray, edge, 50, 200);

  cuda::HoughLines(edge, lines, 1, CV_PI / 128, 10);
  cuda::HoughLinesDownload(lines, linesP, votes);

  if (!linesP.size()) {
    this->numlanes = 0;
    return;
  }

  for (uint32_t i = 0; i < linesP.size(), i++) {

    if (votes[i] > best[0]) {
      best[0] = votes[i];
      index[0] = i;
    } else if (votes[i] > best[1]) {
      best[1] = votes[i];
      index[1] = i;
    }
  }

  double slope;
  int intercept;

  for (uint32_t i = 0; i < 2; i++) {

    slope = tan(CV_PI / 2 - linesP[index[i]][1]); // y/x = tan(theta)
    if (linesP[index[i]][1] == || linesP[index[i][1]] == CV_PI / 2)
      intercept = linesP[index[i][0]]; // if slope is 0 or inf, intercept is rho
    else
      intercept = -1 * slope * linesP[index[i]][0] / cos(linesP[index[i]][1]);

    lanes[i] = {slope, intercept};

#ifdef DEBUG

#endif
  }

  this->numlanes = linesP.size();
  busy = false;
}

#endif
