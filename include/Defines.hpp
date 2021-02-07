
#pragma once 

#include <stdint.h>
#include <string>

// global constants
#define WHEELBASE 31.0f
#define LaneCamFPS 10
#define ObjCamFPS  10
#define NavRefRate 10

#define PI 3.1415926

namespace igv{

// CAMERA DEFINES
enum ID : uint8_t { USB1 = 0 , USB2 = 1 };

// LANE DETECTION DEFINES
#define X0 0
#define Y0 1
#define X1 2
#define Y1 3
//#define _R 0
//#define _THETA 1

// NAVIGATION DEFINES

typedef int8_t Speed;   // special types for easy reading
typedef uint8_t Direction;
typedef int8_t DeltaDir;
typedef double Distance;  // Multi use define

enum Motor: bool {LEFT = false, RIGHT = true};




}
