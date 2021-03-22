/**
 * @file LaneDetection.hpp
 * @brief Contains Prototypes of Lane Detection Functionality
 * @author Orion Serup
 * @bug None
 */

#pragma once

#include "main.hpp"

/**
* @brief namespace for this project
*/
namespace igv{

/**
* @brief Structure to hold the Data for a Lane
*/
struct Lane{

  double slope;  ///< slope of the line
  int intercept; ///< x or y intercept depending on the slope

};

/**
 * @brief Prints a Lane to an Output Stream
 * @param os Output Stream Object
 * @param lane Lane to Print
 * @returns Output stream reference
 */
std::ostream& operator<<(std::ostream& os, Lane& lane);

/**
 * @class LaneDetector 
 * @brief Class that Detects Lanes From Images
 *
 * This Class has both a static function as well as a member function to 
 * Detect Lanes from a standard opencv image type. They have similar algoritms 
 * and nearly the same runtime, if possible, use the member function as it is 
 * thread safe.
 */
class LaneDetector{

public:

  /**
  * @brief Detects Lanes and Fills array with detected lanes
  * @param LaneArray Array of Lanes to be filled
  * @param image Photo To Detect Lanes From
  * @returns Number of Lanes Detected 
  */
  static uint32_t DetectLanes(std::array<Lane, 4>& LaneArray, cv::Mat& image);
  
  /**
  * @brief Detects Lanes and Fills the Private Data with the Lane Data
  * @param Image Photo To Detect Lanes From
  * @returns void
  */
  void DetectLanes(cv::Mat& Image);

  /**
  * @brief Return the Number of Lanes Detected
  * @returns uint32_t: The number of Lanes Detected
  */
  uint32_t GetNumLanes() const { return numlanes; }
  
  /**
  * @brief Return if the Lane Detector is Busy
  * @returns bool: If the LaneDetector is Busy with an Operation
  */
  bool isBusy() const { return busy; }
  
  /**
  * @brief Return the Array full of detected Lanes
  * @returns Array of Lanes used to hold lanes
  */
  const std::array<Lane, 4>& GetLanes() const { return lanes; }

private:

  bool busy;  ///< If the Lane Detector is busy with an operation
  std::array<Lane, 4> lanes;  ///< Array full of viable lanes
  uint32_t numlanes;  ///< Total Number of Lanes Detected

};
  
}


