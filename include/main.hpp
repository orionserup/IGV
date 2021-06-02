/**
 * @file main.hpp
 * @brief Contains all Constants and Standard Functionality
 * @author Orion Serup
 * @bug None
 */

#pragma once 

#include <array>
#include <list>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include <chrono>
#include <thread>
#include <assert.h>

#include "opencv2/opencv.hpp"

#ifdef CUDA
#include "opencv2/"
#endif

// global constants
/// Width of Robot (Wheel Base)
#define WHEELBASE .67f  // meters

/// How Often to Capture an Image
#define LaneCamFPS 10
/// How Often to Capture an Object Image
#define ObjCamFPS  10
/// How Often to Update Course
#define NavRefRate 10
/// How Often to Probe Lidar
#define LIDARFPS   1
/// How Often to Probe GPS
#define GPSFPS     .5f
/// How Often to Probe UltraSonic
#define ULTRAFPS   5

/// PI
#define PI 3.1415926 

/// SPEED OF SOUND
#define VSOUND 346.3  // m/s

/// SPEED OF SOUND /2
#define VSOUND_D2 173.15 // m/s

// CAMERA DEFINES
/// Port of the Lane Cam
#define LANECAMPORT 1
// Port of the Object Cam
#define OBJCAMPORT 0
/// Image Width From Lane Cam
#define LANECAMWIDTH
/// Image Height from Lane Cam
#define LANECAMHEIGHT
/// Image Width from Object Cam 
#define OBJCAMWIDTH
/// Image Height from Object Cam
#define OBJCAMHEIGHT

#ifdef SABERTOOTH
// MOTOR CONTROLLER DEFINES
/// Port of the MotorController Serial
#define MCPORT "/dev/USB"
 
#elif defined(PHIDGET)

#define LEFTMOTORPORT 0
#define RIGHTMOTORPORT 1

#endif

// GPS DEFINES
/// GPS UART PORT
#define GPSPORT "/dev/ttyTHS1"

// LIDAR DEFINES
/// LIDAR USB Port
#define LIDARPORT "/dev/USB"

// LANE DETECTION DEFINES
/// X0 Index
#define X0 0
/// Y0 Index
#define Y0 1
/// X1 Index
#define X1 2
/// Y1 Index
#define Y1 3

#define SPEED_MAX INT8_MAX
#define SPEED_MIN INT8_MIN

// ULTRASONIC DEFINES
/// UltraSonic GPIO In Pin
#define ULTRA_IN  15
/// UltraSonic GPIO Out Pin
#define ULTRA_OUT 12

namespace igv{

// NAVIGATION DEFINES

/// Speed [-127, 127]
typedef int8_t Speed;   // special types for easy reading
/// Direction [0, 255] =  0-2pi
typedef uint8_t Direction;
/// Change In Direction [-127, 127]
typedef int8_t DeltaDir;
/// Distance in Meters
typedef double Distance;  // Multi use define


// Custom Enum Types for Clarity
/// Motor Selection, Left or Right
enum Motor: bool {LEFT = false, RIGHT = true};
/// Lane Selection, 0-3
enum LaneNum : uint8_t{ LO = 0, L1 = 1, L2 = 2, L3 = 3 };


}
