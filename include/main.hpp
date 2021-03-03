
#pragma once 

#include <stdint.h>
#include <array>
#include <list>
#include <unordered_map>
#include <string>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <bits/stdc++.h>

#ifdef DEBUG
#include <assert.h>
#endif

#include "opencv2/opencv.hpp"

// global constants
#define WHEELBASE .67f  // m

#define LaneCamFPS 10
#define ObjCamFPS  10
#define NavRefRate 10
#define LIDARFPS   1
#define GPSFPS     .5f
#define ULTRAFPS   5

#define PI 3.1415926  // m
#define VSOUND 346.3  // m/s
#define VSOUND_D2 173.15 // m/s

// CAMERA DEFINES
#define LANECAMPORT 1
#define OBJCAMPORT 0

// MOTOR CONTROLLER DEFINES
#define MCPORT "/dev/USB"

// GPS DEFINES
#define GPSPORT "/dev/ttyTHS1"

// LIDAR DEFINES
#define LIDARPORT "/dev/USB"

// LANE DETECTION DEFINES
#define X0 0
#define Y0 1
#define X1 2
#define Y1 3
#define _R 0
#define _THETA 1

// ULTRASONIC DEFINES
#define ULTRA_IN  15
#define ULTRA_OUT 12

namespace igv{

// NAVIGATION DEFINES

typedef int8_t Speed;   // special types for easy reading
typedef uint8_t Direction;
typedef int8_t DeltaDir;
typedef double Distance;  // Multi use define


// Custom Enum Types for Clarity
enum Motor: bool {LEFT = false, RIGHT = true};
enum LaneNum : bool{ LO = false, L1 = true };


}
