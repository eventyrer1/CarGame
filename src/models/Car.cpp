#include "models/Car.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include "BoundingBoxHelper.hpp"
#include <iostream>
#include <threepp/audio/Audio.hpp>
#include <utility>
using namespace threepp;

Car::Car(std::shared_ptr<Object3D> model,
         std::shared_ptr<threepp::Scene> scene,
         const std::shared_ptr<threepp::AudioListener> &listener,
         const std::string &audioPath)
    : SpawnableObject(std::move(scene)) {
    if (model) this->Object3D::copy(*model);
    originalTurnSpeed_ = rotationSpeed_;
    // Create follow camera
    camera_ = std::make_unique<PerspectiveCamera>(65.0f, 16.f / 9.f, 0.1f, 100.f);

    this->Object3D::add(*camera_);
    camera_->position.x = 0;
    camera_->position.y = 5;
    camera_->position.z = -13;
    camera_->lookAt(this->position);
    Collidable::computeBoundingSphere(0.6f);
    if (listener && !audioPath.empty()) {
        engineSound_ = std::make_shared<Audio>(*listener, audioPath);
        engineSound_->setLooping(true);
        engineSound_->setVolume(0.5f);
    }
}

std::shared_ptr<Car> Car::create( const std::filesystem::path &path,
    std::shared_ptr<threepp::Scene> scene,
    const std::shared_ptr<threepp::AudioListener> &listener,
    const std::string &audioPath) {

    AssimpLoader loader;
    auto model = loader.load(path);
    if (!model) {
        std::cerr << "Failed to load car model from " << path << std::endl;
        return nullptr;
    }
    model->scale.multiplyScalar(1.0f);
    auto car = std::make_shared<Car>(model,
                                     std::move(scene),
                                     std::shared_ptr<threepp::AudioListener>(listener),
                                     audioPath);
    car->reset();
    return car;
}

PerspectiveCamera &Car::camera() const {
    return *camera_;
}


void Car::update(double deltaTime, CarActions::Move move, CarActions::Turn turn) {
    // Handle movement input
    switch (move) {
        case CarActions::Move::ACCELERATE:
            speed_ += acceleration_ * deltaTime;
            if (speed_ > maxSpeed_) speed_ = maxSpeed_;
            if (engineSound_) {
                engineSound_->play();
                engineSound_->setVolume(0.5f + speed_ / 100);
            }
            break;
        case CarActions::Move::DECELERATE:
            speed_ -= acceleration_ * deltaTime;
            if (speed_ < -maxSpeed_ / 2) speed_ = -maxSpeed_ / 2;
            if (engineSound_) {
                engineSound_->stop();
            }
            break;
        case CarActions::Move::NOTHING:
            speed_ *= 1 - drag_ * deltaTime * 0.1f;
            if (std::abs(speed_) < 0.1f) speed_ = 0;
            if (engineSound_ && speed_ <= 5) {
                engineSound_->stop();
            }
            break;
    }

    // Handle turning
    switch (turn) {
        case CarActions::Turn::TURN_LEFT:
            angle_ += rotationSpeed_ * deltaTime;
            if (engineSound_ && speed_ > 5) {
                engineSound_->play();
            }
            break;
        case CarActions::Turn::TURN_RIGHT:
            angle_ -= rotationSpeed_ * deltaTime;
            if (engineSound_ && speed_ > 5) {
                engineSound_->play();
            }
            break;
        default: break;
    }
    if (speed_ >= -10) {
        camera_->position.z = -13 - speed_ * 0.05f;
        camera_->position.x = 0;
        camera_->position.y = 5;
        camera_->rotation.y = 0;
        //makes the camera look at the car when it reverses
    } else {
        camera_->position.z = 14;
        camera_->position.y = 2;
        camera_->rotation.y = math::PI;
    }
    // Update position & rotation
    this->setRotationFromAxisAngle(Vector3{0, 1, 0}, angle_);
    this->position += Vector3{
        speed_ * std::sin(angle_),
        0,
        speed_ * std::cos(angle_)
    } * static_cast<float>(deltaTime);

    updateBoundingSphere();
    updateBoost(deltaTime);
}

void Car::updateBoundingSphere() {
    boundingSphere_.value().center.copy(position);
}


void Car::onCollision(const std::shared_ptr<Collidable> &other) {
    if (!other) {
        return;
    }

    handleCollisionResponse(other);
    other->collideWith(*this); // double dispatch
}


void Car::handleCollisionResponse(const std::shared_ptr<Collidable> &other) {
    if (!other) {
        return;
    }

    float rebound = -0.2f;
    Vector3 pushDir = position - other->position;
    updateBoundingSphere();
    pushDir.normalize();
    position.add(pushDir.multiplyScalar(0.1f));
    speed_ *= rebound; //makes the car "bounce" back a bit
    updateBoundingSphere();
}

void Car::applyRotationChanger(float amount, double durationSeconds) {
    if (boostTimer_ > 0.0) return;
    originalTurnSpeed_ = rotationSpeed_;
    rotationSpeed_ *= amount;

    boostTimer_ = durationSeconds;
}

void Car::updateBoost(double dt) {
    if (boostTimer_ <= 0.0) return;
    boostTimer_ -= dt;
    if (boostTimer_ <= 0.0) {
        rotationSpeed_ = originalTurnSpeed_;
        boostTimer_ = 0.0;
    }
}

void Car::reset() {
    this->position.set(0, 0, 0);
    this->setRotationFromAxisAngle(Vector3{0, 1, 0}, 0);

    speed_ = 0;
    angle_ = 0;

    // clear active boost
    boostTimer_ = 0.0; //this has to be zero otherwise it will start with boost and test will fail
    rotationSpeed_ = originalTurnSpeed_;
}
