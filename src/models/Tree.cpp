#include "models/Tree.hpp"
#include "BoundingBoxHelper.hpp"
#include <random>

using namespace threepp;

Tree::Tree(std::shared_ptr<Object3D> model, const Vector3& position)
    : model_(std::move(model))
{
    if (model_) {
        add(model_);
        this->position.copy(position);
        updateCollisionBox();
    }
}

std::shared_ptr<Tree> Tree::create(std::shared_ptr<Object3D> model)
{
    if (!model) return nullptr;
    model->scale.multiplyScalar(1.0f);
    auto tree= std::make_shared<Tree>(model);
    tree->updateMatrixWorld(true);
    tree->updateCollisionBox();
    tree->updateHitboxVisualization();
    return tree;
}

void Tree::setRandomPosition(float minX, float maxX, float minZ, float maxZ) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(minX, maxX);
    std::uniform_real_distribution<float> distZ(minZ, maxZ);

    position.set(distX(gen), 0.0f, distZ(gen));

    updateMatrixWorld(true);
    updateCollisionBox();
    updateHitboxVisualization();

}
void Tree::updateCollisionBox() {
    updateMatrixWorld(true);
    collisionBox_ = BoundingBoxHelper::computeTreeCollisionBox(*this);

}
void Tree::setHitboxVisualization(bool enabled, Scene* scene) {
    scene_ = scene;
    if (enabled && !boundingBoxHelper_ && scene_) {
        boundingBoxHelper_ = BoundingBoxHelper::createHelper(collisionBox_, Color::green);
        scene_->add(boundingBoxHelper_);
    } else if (!enabled && boundingBoxHelper_ && scene_) {
        scene_->remove(*boundingBoxHelper_);
        boundingBoxHelper_.reset();
    }
}

void Tree::updateHitboxVisualization() {
    if (boundingBoxHelper_ && scene_) {
        scene_->remove(*boundingBoxHelper_);
        boundingBoxHelper_ = BoundingBoxHelper::createHelper(collisionBox_, Color::green);
        scene_->add(boundingBoxHelper_);
    }
}

// Implement Collidable interface
bool Tree::checkCollision(const Collidable& other) const {
    if (other.getSphere()) {
        return other.getSphere()->intersectsBox(collisionBox_);
    }
    if (other.getBox()) {
        return collisionBox_.intersectsBox(*other.getBox());
    }
    return false;
}

void Tree::onCollision(Collidable* other) {
    //if i ever want to make trees respond to collisions
}