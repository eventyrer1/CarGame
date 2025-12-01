#include "models/Tree.hpp"

using namespace threepp;

Tree::Tree(std::shared_ptr<Object3D> model) {
    if (model) this->copy(*model);
}

std::shared_ptr<Tree> Tree::create(std::shared_ptr<Object3D> model) {
    if (model) {
        auto tree = std::make_shared<Tree>(model);
        tree->updateMatrixWorld(true);
        tree->computeBoundingBox();
        return tree;
    }
    return nullptr;
}

void Tree::computeBoundingBox() {
    updateMatrixWorld(true);
    collisionBox_ = std::make_optional<Box3>(BoundingBoxHelper::computeCollisionBox(*this, 5.0f, 0.5f));
}
