#include "CarVisual.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include <iostream>

using namespace threepp;

CarVisual::CarVisual(std::shared_ptr<Object3D> model) {
    if (model) {
        for (auto& child : model->children) {
            this->add(*child);
        }
    }


    camera_ = std::make_unique<PerspectiveCamera>(65.f, 16.f / 9.f, 0.1f, 100.f);
    this->add(*camera_);
    camera_->position.set(0, 5, -13);
}

std::shared_ptr<CarVisual> CarVisual::create(const std::filesystem::path &path) {
    AssimpLoader loader;
    auto model = loader.load(path);
    if (!model) {
        std::cerr << "Failed to load car model from " << path << std::endl;
        return nullptr;
    }
    model->scale.multiplyScalar(1.0f);
    return std::make_shared<CarVisual>(model);
}

void CarVisual::syncWithLogic(const CarLogic &logic) {
    position.copy(logic.getPosition());
    setRotationFromAxisAngle(Vector3{0, 1, 0}, logic.getAngle());
    camera_->position.set(0, 5, -13);
    camera_->lookAt(Vector3{0, 0, 0});
}

PerspectiveCamera &CarVisual::camera() {
    return *camera_;
}
