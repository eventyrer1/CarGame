#include "CarKeyListener.hpp"
#include <iostream>
using namespace threepp;

void CarKeyListener::onKeyPressed(KeyEvent evt) {
    pressedKeys.insert(evt.key);
}

void CarKeyListener::onKeyReleased(KeyEvent evt) {
    pressedKeys.erase(evt.key);
}

std::pair<CarActions::Move, CarActions::Turn> CarKeyListener::getActions() const {
    using Move = CarActions::Move;
    using Turn = CarActions::Turn;

    Move move = Move::NOTHING;
    Turn turn = Turn::NOTHING;


    if (autoAccelerate_==cameraSteeringEnabled_ && cameraSteeringEnabled_==true) {
        move = Move::ACCELERATE;
    }
    // Manual controls override only when autoAccelerate is off
    else {
        if (pressedKeys.contains(Key::W))
            move = Move::ACCELERATE;
        else if (pressedKeys.contains(Key::S))
            move = Move::DECELERATE;
    }

    float finalTurn = 0.0f;

    // keyboard turn
    if (pressedKeys.contains(Key::A)) finalTurn -= 1.0f;
    else if (pressedKeys.contains(Key::D)) finalTurn += 1.0f;

    // camera turn
    if (cameraSteeringEnabled_==true) {
        finalTurn += cameraTurnValue_;
    }


    if (finalTurn > 0.05f) {
        turn = Turn::TURN_RIGHT;
    }
    else if (finalTurn < -0.05f) {
        turn = Turn::TURN_LEFT;
    }
    else {
        turn = Turn::NOTHING;
    }
    return {move, turn};
}



void CarKeyListener::updateFromCamera(const cv::Mat& frame) {

    cv::Rect box;
    int centerX;
    int centerY;

    // If no human detected
    if (!detector.detect(frame, box, centerX, centerY)) {
        cameraTurnValue_ = -1.0f;
        autoAccelerate_ = false;
        return;
    }

    // Human detected
    autoAccelerate_ = true;

    int mid = frame.cols / 2;
    int offset = centerX - mid;

    // Base turn strength when looking away from target
    const float baseSensitivity = 0.02f;
    float rawTurn = offset * baseSensitivity;

    // turn damping based on how close we are to "aimed"
    const float maxOffset = frame.cols * 0.5f;  // full left-right width
    float normalized = std::abs(offset) / maxOffset; // 0 = centered, 1 = far


    const float minFactor = 0.05f;  // never reduce turning below 5%
    float damping = std::clamp(normalized, minFactor, 1.0f);

    // Apply damping
    cameraTurnValue_ = rawTurn * damping;

    // Clamp final steering range
    cameraTurnValue_ = std::clamp(cameraTurnValue_, -1.0f, 1.0f);
}




