//Inspired from code generated from chatGpt
#include "CarLogic.hpp"
#include <cmath>

using namespace threepp;


void CarLogic::update(double deltaTime, CarActions::Move move, CarActions::Turn turn) {

    switch (move) {
        case CarActions::Move::ACCELERATE:
            speed_ = std::min<float>(speed_ + acceleration_ * deltaTime, maxSpeed_);
            break;
        case CarActions::Move::DECELERATE:
            speed_ = std::max<float>(speed_ - acceleration_ * deltaTime, -maxSpeed_ / 2);
            break;
        case CarActions::Move::NOTHING:
            speed_ *= 1 - drag_ * deltaTime * 0.1f;
            if (std::abs(speed_) < 0.1f) speed_ = 0;
            break;
    }

    if (turn == CarActions::Turn::TURN_LEFT) angle_ += rotationSpeed_ * deltaTime;
    if (turn == CarActions::Turn::TURN_RIGHT) angle_ -= rotationSpeed_ * deltaTime;

    position_ += Vector3{
        speed_ * std::sin(angle_),
        0,
        speed_ * std::cos(angle_)
    } * static_cast<float>(deltaTime);

    boundingSphere_.value().center.copy(position_);
}

void CarLogic::reset() {
    position_.set(0, 0, 0);
    angle_ = 0;
    speed_ = 0;
    Collidable::computeBoundingSphere(0.6f);
}

void CarLogic::onCollision(Collidable* other) {
    handleCollisionResponse(other);
}

void CarLogic::handleCollisionResponse(Collidable* other) {
    Vector3 pushDir = position_ - other->position;
    pushDir.normalize();
    position_.add(pushDir.multiplyScalar(0.1f));
    speed_ *= -0.2f;
}
