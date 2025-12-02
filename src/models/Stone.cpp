#include "models/Stone.hpp"
#include <utility>


using namespace threepp;

Stone::Stone(std::shared_ptr<Object3D> model, std::shared_ptr<threepp::Scene> scene)
    : SpawnableObject(std::move(scene)) {
    if (model) {
        this->copy(*model);
        baseY_ = position.y; // store original height
        time_ = position.z;
        //makes it so that the stone will vary where on the sinus curve it is depending where it is located in the z axis
    }
}

std::shared_ptr<Stone> Stone::create(std::shared_ptr<Object3D> model,
                                     std::shared_ptr<threepp::Scene> scene) {
    if (model) {
        auto stone = std::make_shared<Stone>(model, std::move(scene));
        stone->updateMatrixWorld(true);
        stone->computeBoundingBox();
        return stone;
    }
    return nullptr;
}

void Stone::computeBoundingBox() {
    updateMatrixWorld(true);
    collisionBox_ = std::make_optional<Box3>(
        BoundingBoxHelper::computeCollisionBox(*this, 5.0f, 0.5f)
    );
}

void Stone::update(float dt) {
    time_ += dt;

    const float amplitude = 1.0f; // height of bobbing
    const float speed = 2.0f; // speed of movement

    position.y = baseY_ + std::sinf(time_ * speed) * amplitude;

    updateMatrixWorld(true);
    computeBoundingBox();
}
