//
// Created by evest on 20.11.2025.
//
//much ai was used here
#include "HumanDetector.hpp"

bool HumanDetector::detectAll(const cv::Mat& frame, std::vector<cv::Rect>& humans) {
    seesHuman = false;

    if (frame.empty()) return false;

    cv::cvtColor(frame, hsv_, cv::COLOR_BGR2HSV);

    cv::inRange(
        hsv_,
        cv::Scalar(0, 0, 130),
        cv::Scalar(180, 30, 255),
        mask_
    );

    cv::erode(mask_, mask_, cv::Mat(), cv::Point(-1,-1), 1);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask_, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (auto& c : contours) {
        cv::Rect r = cv::boundingRect(c);
        if (r.area() > 20) {
            humans.push_back(r);
        }
    }

    if (!humans.empty()){
        seesHuman = true;
        return seesHuman;
    }
}


/// Lock onto human closest to center
bool HumanDetector::detect(const cv::Mat& frame, cv::Rect& outBox, int& centerX, int& centerY) {

    seesHuman = false;

    std::vector<cv::Rect> humans;
    if (!detectAll(frame, humans)) {
        return false;
    }

    int imgCenterX = frame.cols / 2;

    int bestIdx = -1;
    int bestDist = 999999;

    // choose the human closest to center horizontally
    for (int i = 0; i < humans.size(); i++) {
        const cv::Rect& r = humans[i];
        int cx = r.x + r.width / 2;
        int dist = std::abs(cx - imgCenterX);

        if (dist < bestDist) {
            bestDist = dist;
            bestIdx = i;
        }
    }

    if (bestIdx < 0) {
        seesHuman = false;
        return false;
    }

    outBox = humans[bestIdx];


    centerX = outBox.x + outBox.width  / 2;
    centerY = outBox.y + outBox.height / 2;


    seesHuman = true;
    return true;
}
