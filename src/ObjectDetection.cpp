
#include "ObjectDetection.hpp"

using namespace igv;

#ifndef CUDA  // if not using the GPU


uint32_t ObjDetector::DetectObjects(list<Object>& objects, Mat& image){
	

	return objects.size();

}

uint32_t ObjDetector::DetectObjects(Mat& Image){


    return this->objects.size();
}

#else

uint32_t ObjDetector::DetectObjects(list<Object>& objs, Mat& Image){

    return objs.size();

}


uint32_t ObjDetector::DetectObjects(Mat& Image){



}

#endif

