

#include "HumanDetector.hpp"

bool HumanDetector::detectAll(const cv::Mat& frame, std::vector<cv::Rect>& humans) {
    seesHuman = false;

    if (frame.empty()) return false;

    cv::cvtColor(frame, hsv_, cv::COLOR_BGR2HSV);

    cv::inRange(
        hsv_,
        cv::Scalar(20, 100, 50),    // lower bound for yellow
        cv::Scalar(35, 255, 255),   // upper bound for yellow
        mask_
    );

    cv::erode(mask_, mask_, cv::Mat(), cv::Point(-1,-1), 1);
//the idea of using contours and much of how to do it was done by AI
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
        hasLock_ = false;
        return false;
    }

    int imgCenterX = frame.cols / 2;

    // If we already have a lock, try to keep it
    if (hasLock_) {

        // Look for a human that overlaps or is close to the old one
        int bestIdx = -1;
        int bestDist = 999999;

        for (int i = 0; i < humans.size(); i++) {
            const cv::Rect& r = humans[i];

            // this was done by AI because of laziness
            int cx = r.x + r.width/2;
            int oldCx = lockedHuman_.x + lockedHuman_.width/2;

            bool overlaps = (r & lockedHuman_).area() > 0;
            int dist = std::abs(cx - oldCx);

            if (overlaps || dist < 80) { // 80px tolerance
                bestIdx = i;
                break;
            }
        }

        // If found → keep lock
        if (bestIdx >= 0) {
            lockedHuman_ = humans[bestIdx];
            outBox = lockedHuman_;
            centerX = lockedHuman_.x + lockedHuman_.width/2;
            centerY = lockedHuman_.y + lockedHuman_.height/2;
            seesHuman = true;
            return true;
        }

        // Otherwise lock is lost
        hasLock_ = false;
    }

    // No lock (new target selection)
    int bestIdx = -1;
    int bestDist = 999999;

    for (int i = 0; i < humans.size(); i++) {
        const cv::Rect& r = humans[i];
        int cx = r.x + r.width/2;
        int dist = std::abs(cx - imgCenterX);

        if (dist < bestDist) {
            bestDist = dist;
            bestIdx = i;
        }
    }

    if (bestIdx < 0) {
        hasLock_ = false;
        return false;
    }

    // Acquire lock
    lockedHuman_ = humans[bestIdx];
    hasLock_ = true;

    outBox = lockedHuman_;
    centerX = lockedHuman_.x + lockedHuman_.width/2;
    centerY = lockedHuman_.y + lockedHuman_.height/2;
    seesHuman = true;

    return true;
}



