/*
#include "models/Car.hpp"
#include "threepp/loaders/AssimpLoader.hpp"

#include <iostream>
using namespace threepp;

Car::Car(std::shared_ptr<Object3D> model) {

    if (model) {
        this->copy(*model);
    }
    //TODO make the visual seperate from the logic

    // Create follow camera
    camera_ = std::make_unique<PerspectiveCamera>(65.f, 16.f / 9.f, 0.1f, 100.f);

    this->add(*camera_);
    camera_->position.set(0, 5, -13);
    camera_->lookAt(this->position);
    Collidable::computeBoundingSphere(0.8f);
}

std::shared_ptr<Car> Car::create(const std::filesystem::path& path) {
    AssimpLoader loader;
    auto model = loader.load(path);
    if (!model) {
        std::cerr << "Failed to load car model from " << path << std::endl;
        return nullptr;
    }
    model->scale.multiplyScalar(1.0f);
    auto car = std::make_shared<Car>(model);
    car->reset();
    return car;
}

PerspectiveCamera& Car::camera() {
    return *camera_;
}

/*void Car::setHitboxVisualization(bool enabled, Scene* scene) {
    scene_ = scene;
    if (enabled && !boundingSphereHelper_ && scene_) {
        auto sphereGeometry = SphereGeometry::create(boundingSphere_.radius, 20, 20);
        auto material = MeshBasicMaterial::create();
        material->wireframe = true;
        material->color = Color::blue;

        boundingSphereHelper_ = Mesh::create(sphereGeometry, material);
        boundingSphereHelper_->position.copy(boundingSphere_.center);
        scene_->add(boundingSphereHelper_);
    } else if (!enabled && boundingSphereHelper_ && scene_) {
        scene_->remove(*boundingSphereHelper_);
        boundingSphereHelper_.reset();
    }
}

void Car::updateHitboxVisualization() {
    if (boundingSphereHelper_ && scene_) {
        boundingSphereHelper_->position.copy(boundingSphere_.center);
    }
}*/

void Car::update(double deltaTime, CarActions::Move move, CarActions::Turn turn) {

    // Handle movement input
    switch (move) {
        case CarActions::Move::ACCELERATE:
            speed_ += acceleration_ * deltaTime;
            if (speed_ > maxSpeed_) speed_ = maxSpeed_;
            break;
        case CarActions::Move::DECELERATE:
            speed_ -= acceleration_ * deltaTime;
            if (speed_ < -maxSpeed_ / 2) speed_ = -maxSpeed_ / 2;
            break;
        case CarActions::Move::NOTHING:
            speed_ *= 1 - drag_ * deltaTime * 0.1f;
            if (std::abs(speed_) < 0.1f) speed_ = 0;
            break;
    }

    // Handle turning
    switch (turn) {
        case CarActions::Turn::TURN_LEFT:
            angle_ += rotationSpeed_ * deltaTime;
            break;
        case CarActions::Turn::TURN_RIGHT:
            angle_ -= rotationSpeed_ * deltaTime;
            break;
        default: break;
    }

    // Update position & rotation

    this->setRotationFromAxisAngle(Vector3{0, 1, 0}, angle_);
    this->position += Vector3{
        speed_ * std::sin(angle_),
        0,
        speed_ * std::cos(angle_)
    } * static_cast<float>(deltaTime);

    updateBoundingSphere();
}

void Car::updateBoundingSphere() {

    boundingSphere_.value().center.copy(position);
    updateHitboxVisualization();
}

/*bool Car::checkCollision(const Collidable& other) const {
    if (other.getBox()) return boundingSphere_.intersectsBox(*other.getBox());
    if (other.getSphere()) return boundingSphere_.intersectsSphere(*other.getSphere());
    return false;
}*/

void Car::onCollision(Collidable* other) {
    handleCollisionResponse(other);
}

void Car::handleCollisionResponse(Collidable* other) {
    Vector3 pushDir = position - other->position;
    pushDir.normalize();
    position.add(pushDir.multiplyScalar(0.1f));
    speed_ *= -0.2f;
    updateBoundingSphere();
}

void Car::reset() {

   this->position.set(0, 0, 0);
   this->setRotationFromAxisAngle(Vector3{0, 1, 0}, 0);

    speed_ = 0;
    angle_ = 0;
}
*/