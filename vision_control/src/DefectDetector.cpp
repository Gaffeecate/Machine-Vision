// src/DefectDetector.cpp
#include "DefectDetector.h"
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

DefectDetector::DefectDetector(int threshold) : threshold_(threshold) {}

bool DefectDetector::detectDefects(const Mat& frame, Mat& output) {
    Mat grayImage, blurredImage, binaryImage;

    // 그레이스케일 변환
    cvtColor(frame, grayImage, COLOR_BGR2GRAY);

    // 노이즈 제거
    GaussianBlur(grayImage, blurredImage, Size(5, 5), 0);

    // 적응형 이진화 (볼펜으로 쓴 글씨를 더 잘 인식)
    adaptiveThreshold(blurredImage, binaryImage, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 11, 2);

    std::vector<std::vector<Point>> contours;
    findContours(binaryImage, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    output = frame.clone();
    bool codeDetected = false;

    for (const auto& contour : contours) {
        double area = contourArea(contour);
        if (area < 50 || area > 10000) continue; // 크기 필터링 조정

        Rect boundingBox = boundingRect(contour);
        double aspectRatio = (double)boundingBox.width / boundingBox.height;

        // 글자나 코드 조각으로 보이는 영역만 선택Q
        if (aspectRatio > 0.1 && aspectRatio < 10) {
            rectangle(output, boundingBox, Scalar(0, 255, 0), 2); // 초록색 박스
            codeDetected = true;
        }
    }

    return codeDetected; // 코드가 감지되면 true 반환
}