
//was done by AI first and debugged and fixed by me later
#include <catch2/catch_test_macros.hpp>
#include <opencv2/opencv.hpp>
#include "HumanDetector.hpp"

// Utility: Create image with background and blobs
static cv::Mat createBlankImage(int w = 320, int h = 240) {
    return cv::Mat(h, w, CV_8UC3, cv::Scalar(0, 0, 0));  // black
}

// Yellow color in BGR that converts into your HSV threshold
static cv::Scalar YELLOW_BGR = cv::Scalar(0, 255, 255); // BGR for yellow

TEST_CASE("detectAll returns false on empty frame") {
    HumanDetector hd;

    cv::Mat empty;
    std::vector<cv::Rect> humans;

    bool result = hd.detectAll(empty, humans);

    CHECK_FALSE(result);
    CHECK(humans.empty());
    CHECK_FALSE(hd.seesHuman);
}

TEST_CASE("detectAll detects yellow blobs") {
    HumanDetector hd;

    cv::Mat img = createBlankImage();
    // Draw small yellow rectangles
    cv::rectangle(img, cv::Rect(10, 10, 30, 30), YELLOW_BGR, cv::FILLED);
    cv::rectangle(img, cv::Rect(100, 50, 20, 20), YELLOW_BGR, cv::FILLED);

    std::vector<cv::Rect> humans;
    bool result = hd.detectAll(img, humans);

    CHECK(result);                 // should return true
    CHECK(hd.seesHuman);           // internal state set
    CHECK(humans.size() >= 2);     // at least two blobs
}

TEST_CASE("detect acquires lock on closest to center") {
    HumanDetector hd;
    cv::Mat img = createBlankImage(200, 200);

    // left yellow blob
    cv::rectangle(img, cv::Rect(20, 80, 40, 40), YELLOW_BGR, cv::FILLED);

    // right yellow blob, closer to center (x=80)
    cv::rectangle(img, cv::Rect(80, 80, 40, 40), YELLOW_BGR, cv::FILLED);

    cv::Rect out;
    int cx = 0, cy = 0;

    bool result = hd.detect(img, out, cx, cy);

    CHECK(result);
    CHECK(hd.seesHuman);

    // Should pick the blob closest to center (the right one)
    CHECK(out.x == 81);
    CHECK(cx > 81);  // center X of rect (have to be 81 since it is until 80 and not until and including)
}

TEST_CASE("detect keeps lock when possible") {
    HumanDetector hd;

    cv::Mat img1 = createBlankImage(200, 200);
    cv::Mat img2 = createBlankImage(200, 200);

    // Frame 1: left blob
    cv::rectangle(img1, cv::Rect(20, 80, 40, 40), YELLOW_BGR, cv::FILLED);

    // Frame 2: blob slightly moved (still near old)
    cv::rectangle(img2, cv::Rect(25, 80, 40, 40), YELLOW_BGR, cv::FILLED);

    cv::Rect out;
    int cx = 0, cy = 0;

    // Acquire initial lock
    CHECK(hd.detect(img1, out, cx, cy));
    int oldX = out.x;

    // Next frame: should keep lock
    CHECK(hd.detect(img2, out, cx, cy));
    CHECK(out.x != 80); // definitely not picking right side
    CHECK(out.x >= oldX);
}

TEST_CASE("detect loses lock when target disappears") {
    HumanDetector hd;

    cv::Mat img1 = createBlankImage(200, 200);
    cv::Mat img2 = createBlankImage(200, 200);

    // Frame 1: blob
    cv::rectangle(img1, cv::Rect(20, 80, 40, 40), YELLOW_BGR, cv::FILLED);

    cv::Rect out;
    int cx = 0, cy = 0;

    // Acquire initial lock
    CHECK(hd.detect(img1, out, cx, cy));
    CHECK(hd.seesHuman);

    // Frame 2: nothing
    bool result = hd.detect(img2, out, cx, cy);

    CHECK_FALSE(result);
    CHECK_FALSE(hd.seesHuman);
}
