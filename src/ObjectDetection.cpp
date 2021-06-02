/**
 * @file ObjectDetection.cpp
 * @author Orion Serup
 * @brief Contains all of the Object Detection Functionality Implementation
 * @bug None
 */

#include "ObjectDetection.hpp"

using namespace igv;
using namespace cv;

// Stream operator allows the lanes to be printed to file of stdout
ostream& igv::operator<<(ostream &os, Object &obj)
{

    os << "Object Type " << obj.classification << endl;
    os << "At Left Angle " << obj.leftedge << endl;
    os << "Until Right Angle" << obj.rightedge << endl;
    os << "With Distance " << obj.distance << endl;

    return os;
}

#ifndef CUDA // if not using the GPU

uint32_t ObjDetector::DetectObjects(list<Object> &objects, Mat &image1, Mat& image2)
{

    Ptr<FastFeatureDetector> fd = FastFeatureDetector::create(20);

    std::vector<KeyPoint> keypoints[2];

    fd->detect(image1, keypoints[0]);
    fd->detect(image2, keypoints[1]);

    #ifdef DEBUG
    
    Mat dest;
    drawKeypoints(image, keypoints, dest);
    imshow("Key Points on Image", dest);

    #endif

    for(uint8_t i = 0; i < MIN(keypoints[0].size(), keypoints[1].size()); i++) {

        objects[i]

    }

    return objects.size();
}

void ObjDetector::DetectObjects(Mat &Image)
{


}

#else

uint32_t ObjDetector::DetectObjects(list<Object> &objs, Mat &Image)
{

    return objs.size();
}

uint32_t ObjDetector::DetectObjects(Mat &Image)
{

    busy = true;

    busy = false;

    return objs.size();
}

#endif

// ###using Yolo as model

// import cv2 as cv2
// import numpy as np
// from imutils.video import FPS
// import imutils

// # Load Yolo
// net = cv2.dnn.readNet("yolo.weights", "yolo.cfg")
// classes = []
// with open("coco.names", "r") as f:
//     classes = [line.strip() for line in f.readlines()]
// layer_names = net.getLayerNames()
// output_layers = [layer_names[i[0] - 1] for i in net.getUnconnectedOutLayers()]
// colors = np.random.uniform(0, 255, size=(len(classes), 3))

// # Loading image
// img = cv2.imread("approach3.PNG")
// img = cv2.resize(img, None, fx=0.4, fy=0.4)
// height, width, channels = img.shape

// # Detecting objects
// blob = cv2.dnn.blobFromImage(img, 0.00392, (416, 416), (0, 0, 0), True, crop=False)
// net.setInput(blob)
// outs = net.forward(output_layers)

// # Showing informations on the screen
// class_ids = []
// confidences = []
// boxes = []
// for out in outs:
//     for detection in out:
//         scores = detection[5:]
//         class_id = np.argmax(scores)
//         confidence = scores[class_id]
//         if confidence > 0.5:
//             # Object detected
//             center_x = int(detection[0] * width)
//             center_y = int(detection[1] * height)
//             w = int(detection[2] * width)
//             h = int(detection[3] * height)
//             # Rectangle coordinates
//             x = int(center_x - w / 2)
//             y = int(center_y - h / 2)
//             boxes.append([x, y, w, h])
//             confidences.append(float(confidence))
//             class_ids.append(class_id)

// indexes = cv2.dnn.NMSBoxes(boxes, confidences, 0.5, 0.4)

// font = cv2.FONT_HERSHEY_PLAIN
// for i in range(len(boxes)):
//     if i in indexes:
//         x, y, w, h = boxes[i]
//         label = str(classes[class_ids[i]])
//         color = colors[i]
//         cv2.rectangle(img, (x, y), (x + w, y + h), color, 2)
//         cv2.putText(img, label, (x, y - 10), font, 1.5, color, 3)

// cv2.imshow("approach3.PNG", img)
// cv2.waitKey(0)
// cv2.destroyAllWindows()
