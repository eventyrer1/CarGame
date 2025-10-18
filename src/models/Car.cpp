#include "models/Car.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include "BoundingBoxHelper.hpp"
using namespace threepp;

Car::Car(std::shared_ptr<Object3D> model)
    : model_(std::move(model))
{
    if (model_) {
        add(model_);

        // Compute local bounding box once (in model's local space)
        localBoundingBox_ = BoundingBoxHelper::computeBoundingBox(*model_);

        // Initialize world bounding box
        updateBoundingBox();
    }

    camera_ = std::make_unique<PerspectiveCamera>(65.f, (16/9.f), 0.1f, 100.f);
    camera_->rotation.x = 0.f * math::DEG2RAD;

    if (model_) {
        model_->add(*camera_);
        camera_->position.set(0, 5, -13);
        camera_->lookAt(model_->position);
    }
}

std::shared_ptr<Car> Car::create(const std::filesystem::path &path) {
    AssimpLoader loader;
    auto model = loader.load(path);
    if (!model) return nullptr;
    model->scale.multiplyScalar(1.0f);
    return std::make_shared<Car>(model);
}

PerspectiveCamera &Car::camera() {
    return *camera_;
}

void Car::setHitboxVisualization(bool enabled) {
    if (enabled && !boundingBoxHelper_) {
        boundingBoxHelper_ = BoundingBoxHelper::createHelper(boundingBox_, Color::red);
        add(boundingBoxHelper_);
    } else if (!enabled && boundingBoxHelper_) {
        remove(*boundingBoxHelper_);
        boundingBoxHelper_.reset();
    }
}

void Car::updateHitboxVisualization() {
    if (boundingBoxHelper_) {
        // Remove old helper
        remove(*boundingBoxHelper_);
        // Create new one with updated bounding box
        boundingBoxHelper_ = BoundingBoxHelper::createHelper(boundingBox_, Color::red);
        add(boundingBoxHelper_);
    }
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
            if (speed_ < -maxSpeed_ / 2) speed_ = -maxSpeed_ / 2;
            break;
        case CarKeyListener::CarActionMove::NOTHING:
            speed_ *= 1 - 0.10 * deltaTime;
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
    model_->position += (Vector3{speed_ * std::sin(angle_), 0, speed_ * std::cos(angle_)} *
                        static_cast<float>(deltaTime));

    // Efficient bounding box update - just transform the local box
    updateBoundingBox();
    
    // Update debug visualization if enabled
    updateHitboxVisualization();
}

// Private helper to update the world-space bounding box
void Car::updateBoundingBox() {
    boundingBox_.copy(localBoundingBox_);
    // Apply the car's world transformation to the local bounding box
    Matrix4 matrix;
    matrix.compose(model_->position, model_->quaternion, model_->scale);
    boundingBox_.applyMatrix4(matrix);
}