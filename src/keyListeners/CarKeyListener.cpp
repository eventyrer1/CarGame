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


    if (autoAccelerate==cameraSteeringEnabled) {
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
    if (cameraSteeringEnabled==true) {
        finalTurn += cameraTurnValue;
    }


    if (finalTurn > 0.05f)          turn = Turn::TURN_RIGHT;
    else if (finalTurn < -0.05f)   turn = Turn::TURN_LEFT;
    else                           turn = Turn::NOTHING;

    return {move, turn};
}



void CarKeyListener::updateFromCamera(const cv::Mat& frame) {

    cv::Rect box;
    int centerX;
    int centerY;

    if (!detector.detect(frame, box, centerX,centerY)) {
        cameraTurnValue = -1.0f;
        autoAccelerate = false;       // no human → do NOT accelerate
        return;
    }

    autoAccelerate = true;            // human seen → start accelerating

    int middle = frame.cols / 2;
    int offset = centerX - middle;

    float sensitivity = 0.002f;
    cameraTurnValue = offset * sensitivity;

    if (cameraTurnValue > 1.0f) cameraTurnValue = 1.0f;
    if (cameraTurnValue < -1.0f) cameraTurnValue = -1.0f;
}


