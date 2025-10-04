#include "../../include/models/car.hpp"
#include "threepp/loaders/AssimpLoader.hpp"

using namespace threepp;

car::car(std::shared_ptr<Object3D> model)
    : model_(std::move(model)), speed_(0.0f), maxSpeed_(20.0f),
      acceleration_(5.0f), rotationSpeed_(2.0f)
{
    if (model_) add(model_);
}

// Factory method
std::shared_ptr<car> car::create(const std::filesystem::path& path) {
    AssimpLoader loader;
    auto model = loader.load(path);
    if (!model) return nullptr;
    model->scale.multiplyScalar(1.0f);
    return std::make_shared<car>(model);
}
