/**
 * @file ObjectDetection.cpp
 * @author Orion Serup
 * @brief Contains all of the Object Detection Functionality Implementation
 * @bug None
 */
#include "ObjectDetection.hpp"

using namespace igv;

// Stream operator allows the lanes to be printed to file of stdout
ostream& igv::operator<<(ostream& os, Object& obj){

    os << "Object Type " << obj.classification << endl;
    os << "At Angle " << obj.angle << endl;
    os << "With Distance " << obj.distance << endl;
    
    return os;
}

#ifndef CUDA  // if not using the GPU

uint32_t ObjDetector::DetectObjects(list<Object>& objects, Mat& image){
	
    return objects.size();

}

uint32_t ObjDetector::DetectObjects(Mat& Image){

    busy = true;

    busy = false;

    return this->objects.size();
}

#else

uint32_t ObjDetector::DetectObjects(list<Object>& objs, Mat& Image){

    return objs.size();

}


uint32_t ObjDetector::DetectObjects(Mat& Image){

    busy = true;

    busy = false;

    return objs.size();

}

#endif

