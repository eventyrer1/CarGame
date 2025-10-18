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
        boundingBox_ = BoundingBoxHelper::computeBoundingBox(*this);
    }
}

std::shared_ptr<Tree> Tree::create(std::shared_ptr<Object3D> model)
{
    if (!model) return nullptr;
    model->scale.multiplyScalar(501.0f);
    return std::make_shared<Tree>(model);
}

void Tree::setRandomPosition(float minX, float maxX, float minZ, float maxZ) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(minX, maxX);
    std::uniform_real_distribution<float> distZ(minZ, maxZ);

    position.set(distX(gen), 0.0f, distZ(gen));

    // Update bounding box after position change
    boundingBox_ = BoundingBoxHelper::computeBoundingBox(*this);
    updateHitboxVisualization();
}

void Tree::setHitboxVisualization(bool enabled, Scene* scene) {
    scene_ = scene;
    if (enabled && !boundingBoxHelper_ && scene_) {
        boundingBoxHelper_ = BoundingBoxHelper::createHelper(boundingBox_, Color::green);
        scene_->add(boundingBoxHelper_);
    } else if (!enabled && boundingBoxHelper_ && scene_) {
        scene_->remove(*boundingBoxHelper_);
        boundingBoxHelper_.reset();
    }
}

void Tree::updateHitboxVisualization() {
    if (boundingBoxHelper_ && scene_) {
        scene_->remove(*boundingBoxHelper_);
        boundingBoxHelper_ = BoundingBoxHelper::createHelper(boundingBox_, Color::green);
        scene_->add(boundingBoxHelper_);
    }
}