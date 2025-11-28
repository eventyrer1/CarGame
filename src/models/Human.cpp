#include "models/Human.hpp"

#include "ScoreManager.hpp"
#include "models/Car.hpp"
using namespace threepp;

Human::Human(std::shared_ptr<Object3D> model,
             AudioListener* listener,
             const std::string& soundPath,
             ScoreManager* scoreManager)
    : scoreManager_(scoreManager) {

    if (model) {
        this->copy(*model);

        this->scale.multiplyScalar(2);
    }
        if (listener) {
        collisionSound_ = std::make_shared<threepp::PositionalAudio>(*listener, soundPath);
        Object3D::add(*collisionSound_);
    }
}

std::shared_ptr<Human> Human::create(std::shared_ptr<Object3D> model,
                                     AudioListener* listener,
                                     const std::string& soundPath,
                                     ScoreManager* scoreManager) {
    if (!model) return nullptr;

    auto human = std::make_shared<Human>(model, listener, soundPath,scoreManager);
    human->updateMatrixWorld(true);
    human->computeBoundingBox();
    return human;
}

void Human::computeBoundingBox() {

    updateMatrixWorld(true);
    collisionBox_ = std::make_optional<Box3>(BoundingBoxHelper::computeCollisionBox(*this));
}

void Human::onCollision(Collidable* other) {
    handleCollisionResponse(other);
}

void Human::collideWith(Car& car) {
    // Car interacts with Human as power-up; Car owns logic, but we can flag consumption state.
    if (!hit_) {
        handleCollisionResponse(&car);
        car.applySpeedBoost(50.f, 5.0); // parameters are tunable; decoupled via Car's public API
    }
}

void Human::handleCollisionResponse(Collidable* /*other*/) {
    if (hit_) return;
    hit_ = true;

    // visual response
    this->rotateX(math::degToRad(90));
    this->position.y -= 0.5f;
    updateMatrixWorld(true);

    // move this human's hitbox far away so it never collides again
    if (collisionBox_) {
        collisionBox_->set(
                Vector3(9999, 9999, 9999),
                Vector3(10000, 10000, 10000)
        );
    }


    if (collisionSound_ && !collisionSound_->isPlaying()) {
        collisionSound_->play();
    }
    if (scoreManager_) {
        scoreManager_->addHit();
    }

}
void Human::reset(float minX, float maxX, float minZ, float maxZ) {
    hit_ = false;

    // restore default pose
    this->rotation.set(0, 0, 0);
    this->position.y = 0;

    // random spawn from SpawnableObject
    setRandomPosition(minX, maxX, minZ, maxZ);

    updateMatrixWorld(true);
    computeBoundingBox();
}