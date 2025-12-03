#include "models/Tree.hpp"
#include <utility>


using namespace threepp;

Tree::Tree(const std::shared_ptr<Object3D> &model, std::shared_ptr<threepp::Scene> scene)
    : SpawnableObject(std::move(scene)) {
    if (model) this->Object3D::copy(*model);
}

std::shared_ptr<Tree> Tree::create(std::shared_ptr<Object3D> model, std::shared_ptr<threepp::Scene> scene) {
    if (model) {
        auto tree = std::make_shared<Tree>(model, std::move(scene));
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
