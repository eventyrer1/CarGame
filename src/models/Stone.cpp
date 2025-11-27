//
// Created by evest on 27.11.2025.
//
#include "models/Stone.hpp"

using namespace threepp;

Stone::Stone(std::shared_ptr<Object3D> model) {
    if (model) this->copy(*model);
}

std::shared_ptr<Stone> Stone::create(std::shared_ptr<Object3D> model) {
    if (model) {
        auto stone = std::make_shared<Stone>(model);
        stone->updateMatrixWorld(true);
        stone->computeBoundingBox();
        return stone;
    }
    return nullptr;
}

void Stone::computeBoundingBox() {
    updateMatrixWorld(true);
    collisionBox_ = std::make_optional<Box3>(BoundingBoxHelper::computeCollisionBox(*this, 5.0f, 0.5f));
}