
#include "ObjectDetection.hpp"

using namespace igv;

#ifndef CUDA  // if not using the GPU

ObjDetector::ObjDetector(Camera& cam): cam(cam){}

uint32_t ObjDetector::DetectObjects(vector<Object>& objects, Mat& image){
	

	
}

uint32_t ObjDetector::DetectObjects(Mat& Image){



}

#else

uint32_t ObjDetector::DetectObjects(vector<Object>& objs, Mat& Image){



}


uint32_t ObjDetector::DetectObjects(Mat& Image){



}

#endif

