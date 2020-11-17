
#define HAVE_OPENCV_IMGPROC
#define HAVE_OPENCV_PHOTO

#include "opencv.hpp"
#include "hal.hpp"

using namespace cv;

class ObjectDetector{

public:

    ObjectDetector(HardwareInterface* hal);
    ObjectDetector();

    void ReadImage( unsigned char bytemask ) const;
    Mat GetImage( int Loc = 0) { return hal->cam[Loc].GetImage(); }

private:

    HardwareInterface* hal;

};


