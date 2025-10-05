#include "../../include/models/Car.hpp"

#include <iostream>

#include "threepp/loaders/AssimpLoader.hpp"

using namespace threepp;

Car::Car(std::shared_ptr<Object3D> model)
    : model_(std::move(model)) {
    if (model_) add(model_);
}

// Factory method
std::shared_ptr<Car> Car::create(const std::filesystem::path &path) {
    AssimpLoader loader;
    auto model = loader.load(path);
    if (!model) return nullptr;
    model->scale.multiplyScalar(1.0f);
    return std::make_shared<Car>(model);
}

void Car::update(double deltaTime,
                 std::pair<CarKeyListener::CarActionMove, CarKeyListener::CarActionTurn> actions) {
    switch (actions.first) {
        case CarKeyListener::CarActionMove::ACCELERATE:
            speed_ += acceleration_ * deltaTime;
            if (speed_ > maxSpeed_) speed_ = maxSpeed_;
            break;
        case CarKeyListener::CarActionMove::DECELERATE:
            speed_ -= acceleration_ * deltaTime;
            if (speed_ < -maxSpeed_ / 2) speed_ = -maxSpeed_ / 2; // Allow some reverse speed
            break;
        case CarKeyListener::CarActionMove::NOTHING:
            speed_ *= 1 - 0.10 * deltaTime; // Friction factor

            break;
    }

    switch (actions.second) {
        case CarKeyListener::CarActionTurn::TURN_LEFT:
            angle_ += rotationSpeed_ * deltaTime;
            break;
        case CarKeyListener::CarActionTurn::TURN_RIGHT:
            angle_ -= rotationSpeed_ * deltaTime;
            break;
    }
    model_->setRotationFromAxisAngle(Vector3{0, 1, 0}, angle_);
    // Update position based on speed and direction
    model_->position += (Vector3{speed_ * std::sin(angle_), 0, speed_ * std::cos(angle_)} * static_cast<float>(
                             deltaTime));
}
