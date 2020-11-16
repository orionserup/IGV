#pragma once

#include "ObjectDetection.hpp"
#include "BasicNavigation.hpp"
#include "hal.hpp"
#include <vector>

using namespace std;

void Initialize(vector<ObjectDetector>& detectors, HardwareInterface& hal );
void run(vector<ObjectDetector>& detectors);

