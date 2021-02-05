#pragma once

#include "opencv2/opencv.hpp"
#include "Hardware/Peripherals.hpp"
#include <string>
#include <array>

using namespace cv;
using namespace std;

namespace igv {

typedef uint8_t Speed;   // special types for easy reading
typedef uint8_t Direction;
typedef double Distance;
typedef int8_t DeltaDir;

enum Location: uint8_t { LEFT = 0, RIGHT = 1 };
enum ID : uint8_t { INT = 0, USB = 1 };

/* Hardware Interface Structure
*
*   FUNCTIONALITY:  Acts as a middle man between the Software and the Hardware, Almost a firmware of sorts
*   CONTAINS:       Holds Objects connected to hardware, they can be accessed using hal.object[index].function() or HardwareInterface::Object::Function()
*   DEPENDENCIES:   Has no Depencies other than just typename dependencies from namespace cv and std
*   
*/ 

class HardwareInterface{  

public:

    class Camera {  // Camera Class, GetImage Calls to either ROS api or to the nano Camera API

    public:

        Camera(ID id);
        Camera(VideoCapture& capture);

        inline Mat& GetImage() { return Image; }
        void Capture();

    private:
        
        Mat Image;
        VideoCapture cap;

    };

    class Motor{

    public:

      Motor(Location loc);

      void SetSpeed(Speed speed);
      inline Speed GetSpeed() const { return this->myspeed; } 
      inline Location GetLocation() const { return this->myloc; }

    private:

      Speed myspeed;
      Location myloc;

    };

    class LIDAR{

    public:
      
      void Probe();

        

    }; 

    class UltraSonic{

    public:

      double GetDistance(){ return this->distance; }  // returns the probed distance
      void Probe();  // gets a reading and puts it in the distance value

    private:

      double distance;

    };

    class GPS{
    
    public:

      void Probe();
      double GetLatitude() { return Lat; }
      double GetLongitude() { return Long; }

    private:

      double Lat, Long;

    };

    HardwareInterface();        // initializes the hardware interface, IO, etc

    Camera LaneCam, ObjCam;     // the interface holds the cameras,
    Motor lmotor, rmotor;       // motors,
    GPS gps;                    // GPS modules,
    LIDAR lidar;                // lidar,
    UltraSonic ultra;           // and UltraSonic Sensors so that the other modules can control peripherals without IO manip

};

}
