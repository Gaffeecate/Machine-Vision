// include/DefectDetector.h
#ifndef DEFECT_DETECTOR_H
#define DEFECT_DETECTOR_H

#include <opencv2/opencv.hpp>

class Defect_Detector {
public:
    Defect_Detector(int threshold = 100);
    bool detectDefects(const cv::Mat& frame, cv::Mat& output);
private:
    int threshold_;
};

#endif // DEFECTDETECTOR_H