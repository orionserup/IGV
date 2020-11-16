
#define HAVE_OPENCV_IMGPROC
#define HAVE_OPENCV_PHOTO

#include "opencv.hpp"
#include <vector>
#include "hal.hpp"

using namespace cv;

class ObjectDetector{

public:

    ObjectDetector(Camera& MyCamera);
    void SetCamera(Camera& cam);
    void ReadImage( byte bytemask ) const;

private:

    Mat& MyImage;
    Camera& MyCamera;

};


