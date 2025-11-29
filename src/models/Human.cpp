#include "models/Human.hpp"
#include "ScoreManager.hpp"
#include "models/Car.hpp"

using namespace threepp;

Human::Human(std::shared_ptr<Object3D> model,
             AudioListener* listener,
             const std::vector<std::string>& soundPaths,
             ScoreManager* scoreManager)
    : listener_(listener),
      soundPaths_(soundPaths),
      scoreManager_(scoreManager) {

    if (model) {
        this->copy(*model);
        this->scale.multiplyScalar(2);
    }
}

std::shared_ptr<Human> Human::create(std::shared_ptr<Object3D> model,
                                     AudioListener* listener,
                                     const std::vector<std::string>& soundPaths,
                                     ScoreManager* scoreManager) {

    if (!model) return nullptr;

    auto human = std::make_shared<Human>(model, listener, soundPaths, scoreManager);
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
    if (!hit_) {
        handleCollisionResponse(&car);
        car.applySpeedBoost(50.f, 5.0f);
    }
}

void Human::handleCollisionResponse(Collidable* /*other*/) {
    if (hit_) return;
    hit_ = true;

    // visual flatten
    this->rotateX(math::degToRad(90));
    this->position.y -= 0.5f;
    updateMatrixWorld(true);

    // disable collision
    if (collisionBox_) {
        collisionBox_->set(
            Vector3(9999, 9999, 9999),
            Vector3(10000, 10000, 10000)
        );
    }

    // PLAY RANDOM SOUND (Originally made by ai but edited a lot by me)
    if (listener_ && !soundPaths_.empty()) {

        int idx = rand() % soundPaths_.size();
        std::string chosen = soundPaths_[idx];

        collisionSound_ = std::make_shared<threepp::PositionalAudio>(*listener_, chosen);
        collisionSound_->setVolume(8.0f);
        Object3D::add(*collisionSound_);
        collisionSound_->play();
    }

    // add score once
    if (scoreManager_) {
        scoreManager_->addHit();
    }
}

void Human::reset(float minX, float maxX, float minZ, float maxZ) {
    hit_ = false;

    this->rotation.set(0, 0, 0);
    this->position.y = 0;

    setRandomPosition(minX, maxX, minZ, maxZ);

    updateMatrixWorld(true);
    computeBoundingBox();
}
