#include "models/Car.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include "BoundingBoxHelper.hpp"


using namespace threepp;

Car::Car(std::shared_ptr<Object3D> model)
    : model_(std::move(model))
{
    if (model_) {
        add(model_);
    }

    camera_ = std::make_unique<PerspectiveCamera>(65.f, (16/9.f), 0.1f, 100.f);
    camera_->rotation.x = 0.f * math::DEG2RAD;

    if (model_) {
        model_->add(*camera_);
        camera_->position.set(0, 5, -13);
        camera_->lookAt(model_->position);
        
        boundingSphere_ = BoundingBoxHelper::computeBoundingSphere(*model_, 0.8f);
    }
}

std::shared_ptr<Car> Car::create(const std::filesystem::path &path) {
    AssimpLoader loader;
    auto model = loader.load(path);
    if (!model) {

        return std::make_shared<Car>(nullptr);
    }
    model->scale.multiplyScalar(1.0f);
    return std::make_shared<Car>(model);
}

PerspectiveCamera &Car::camera() {
    return *camera_;
}

void Car::setHitboxVisualization(bool enabled, Scene* scene) {
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
}

void Car::update(double deltaTime,
                 const CarActions::Move moveAction, const CarActions::Turn turnAction) {

    // Apply speed logic (works even if model_ is nullptr)
    switch (moveAction) {
        case CarActions::Move::ACCELERATE:
            speed_ += acceleration_ * deltaTime;
            if (speed_ > maxSpeed_) speed_ = maxSpeed_;
            break;
        case CarActions::Move::DECELERATE:
            speed_ -= acceleration_ * deltaTime;
            if (speed_ < -maxSpeed_ / 2) speed_ = -maxSpeed_ / 2;
            break;
        case CarActions::Move::NOTHING:

            if (abs(speed_)>1) {
                speed_ *= 1 - 0.10 * deltaTime*drag_;
            }
            else speed_*=0;
            break;
    }

    switch (turnAction) {
        case CarActions::Turn::TURN_LEFT:
            angle_ += rotationSpeed_ * deltaTime;
            break;
        case CarActions::Turn::TURN_RIGHT:
            angle_ -= rotationSpeed_ * deltaTime;
            break;
        case CarActions::Turn::NOTHING:
            break;
    }

    // Only update model if it exists
    if (model_) {
        model_->setRotationFromAxisAngle(Vector3{0, 1, 0}, angle_);
        model_->position += (Vector3{speed_ * std::sin(angle_),0, speed_ * std::cos(angle_)} *
                             static_cast<float>(deltaTime));
    }

    updateBoundingSphere();
}

void Car::updateBoundingSphere() {
    if (model_) {
        boundingSphere_.center.copy(model_->position);
        updateHitboxVisualization();
    }
}

// Implement Collidable interface
bool Car::checkCollision(const Collidable& other) const {
    if (other.getBox()) {
        return boundingSphere_.intersectsBox(*other.getBox());
    }
    if (other.getSphere()) {
        return boundingSphere_.intersectsSphere(*other.getSphere());
    }
    return false;
}

void Car::onCollision(Collidable* other) {

    handleCollisionResponse(other);
}

void Car::handleCollisionResponse(Collidable* other) {
    // Push car away from collision
    Vector3 pushDirection = getPosition() - other->getPosition();

    pushDirection.normalize();
    

    model_->position.add(pushDirection.multiplyScalar(0.1f));
    

    speed_ *= 0.5f;
    
    // Update collision sphere
    updateBoundingSphere();
}
void Car::reset() {
    model_->position.set(0, 0, 0);
    speed_ = 0;
    angle_ = 0;
    maxSpeed_ = 100;
    acceleration_ = 100;
    rotationSpeed_ = 2;
    drag_ = 10.f;



}
