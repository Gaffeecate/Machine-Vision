// src/main.cpp
#include <opencv2/opencv.hpp>
#include "DefectDetector.h"

using namespace std;
using namespace cv;

int main() {
    VideoCapture cap(0); // 웹캠 열기
    if (!cap.isOpened()) {
        std::cerr << "웹캠을 열 수 없습니다!" << std::endl;
        return -1;
    }

    DefectDetector detector(100); // 임계값 100 설정
    Mat frame, detectedFrame;

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        if (detector.detectDefects(frame, detectedFrame)) {
            std::cout << "결함이 감지되었습니다!" << std::endl;
            imshow("Detected Defects", detectedFrame);
            imwrite("defect_detected.png", detectedFrame); // 캡쳐 및 저장
        }

        if (waitKey(30) >= 0) break;
    }

    return 0;
}
