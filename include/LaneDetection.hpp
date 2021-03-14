#pragma once

#include "main.hpp"
#include "Camera.hpp"

/*!
* \namespace igv
* \brief namespace for this project
*/
namespace igv{

/*!
* \class Lane
* \brief Structure to hold the Data for a Lane
*/
struct Lane{

  double slope;
  int intercept;

};

/*!
* \fn operator<<(std::ostream& os, Lane& lane)
* \param os Output Stream Object
* \param lane Lane to Print
* \returns std::ostream&
*/
std::ostream& operator<<(std::ostream& os, Lane& lane);

/*!
* \class LaneDetector
* \brief Class that Detects Lanes From Images
*/
class LaneDetector{

public:

  /*!
  * \fn DetectLanes(std::array<Lane, 4>& LaneArray, cv::Mat& image)
  * \brief Detects Lanes and Fills array with detected lanes
  * \param LaneArray Array of Lanes to be filled
  * \param image Photo To Detect Lanes From
  * \returns uint32_t 
  */
  static uint32_t DetectLanes(std::array<Lane, 4>& LaneArray, cv::Mat& image);
  
  /*!
  * \fn DetectLanes(cv::Mat& image)
  * \brief Detects Lanes and Fills the Private Data with the Lane Data
  * \param Image Photo To Detect Lanes From
  * \returns void
  */
  void DetectLanes(cv::Mat& Image);

  /*!
  * \fn GetNumLanes()
  * \brief Return the Number of Lanes Detected
  * \returns uint32_t
  */
  uint32_t GetNumLanes() { return numlanes; }
  
  /*!
  * \fn isBusy()
  * \brief Return if the Lane Detector is Busy
  * \returns bool
  */
  bool isBusy(){ return busy; }
  
  /*!
  * \fn GetLanes()
  * \brief Return the Array full of detected Lanes
  * \returns std::array<Lane, 4>&
  */
  std::array<Lane, 4>& GetLanes() { return lanes; }

private:

  bool busy;
  std::array<Lane, 4> lanes;
  uint32_t numlanes;

};
  
}


