#include "models/Car.hpp"



#include "threepp/loaders/AssimpLoader.hpp"

using namespace threepp;

Car::Car(std::shared_ptr<Object3D> model)
    : model_(std::move(model))
{
    if (model_) {
        add(model_);
    }

    camera_ = std::make_unique<PerspectiveCamera>(65.f,1.f, 0.1f, 100.f);
    camera_->rotation.x = 0.f * math::DEG2RAD; // tilt down 10 degrees

    // Attach camera to the model instead of the Car object
    if (model_) {
        model_->add(*camera_);


        // Position the camera relative to the model
        camera_->position.set(0, 5, -13);
        camera_->lookAt(model_->position);

    }
    }


// Factory method
std::shared_ptr<Car> Car::create(const std::filesystem::path &path) {
    AssimpLoader loader;
    auto model = loader.load(path);
    if (!model) return nullptr;
    model->scale.multiplyScalar(1.0f);
    return std::make_shared<Car>(model);


}

PerspectiveCamera &Car::camera()        {

    return *camera_;
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

    //tatt fra sphero.cpp


}
