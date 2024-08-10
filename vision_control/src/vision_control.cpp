#include "../include/Defect_Detector.h"
#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    cv::VideoCapture cap(0); // 웹캠 열기
    if (!cap.isOpened()) {
        std::cerr << "웹캠을 열 수 없습니다!" << std::endl;
        return -1;
    }

    Defect_Detector detector(100); // 임계값 100 설정
    cv::Mat frame, detectedFrame;

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "프레임을 캡처할 수 없습니다." << std::endl;
            break;
        }

        try {
            cv::imshow("Camera Feed", frame); // 항상 원본 프레임을 표시
            if (detector.detectDefects(frame, detectedFrame)) {
                std::cout << "결함이 감지되었습니다!" << std::endl;
                cv::imshow("Camera Feed", detectedFrame);
            }
        }
        catch (const cv::Exception& e) {
            std::cerr << "OpenCV 오류: " << e.what() << std::endl;
            break;
        }

        if (cv::waitKey(30) >= 0) break;
    }

    return 0;
}