//
// Created by evest on 20.11.2025.
//

#ifndef CARGAME_HUMANDETECTOR_H
#define CARGAME_HUMANDETECTOR_H
#include <opencv2/opencv.hpp>

class HumanDetector {
public:
    bool detectAll(const cv::Mat& frame, std::vector<cv::Rect>& humans);
    bool detect(const cv::Mat& frame, cv::Rect& outBox, int& centerX, int& centerY);

    bool seesHuman = false;

private:
    cv::Rect lockedHuman_;
    bool hasLock_ = false;
    cv::Mat hsv_;
    cv::Mat mask_;
};


#endif //CARGAME_HUMANDETECTOR_H