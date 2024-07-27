// include/DefectDetector.h
#ifndef DEFECTDETECTOR_H
#define DEFECTDETECTOR_H

#include <opencv2/opencv.hpp>

class DefectDetector {
public:
    DefectDetector(int threshold = 100);
    bool detectDefects(const cv::Mat& frame, cv::Mat& output);
private:
    int threshold_;
};

#endif // DEFECTDETECTOR_H