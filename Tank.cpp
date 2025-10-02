
#include "Tank.hpp"
#include "threepp/loaders/AssimpLoader.hpp"

using namespace threepp;
//used ai for much of this code
Tank::Tank(std::shared_ptr<Object3D> model)
    : model_(std::move(model))
{
    if (model_) add(model_);
}

std::shared_ptr<Tank> Tank::create(const std::filesystem::path& path) {
    AssimpLoader loader;
    auto model = loader.load(path);
    if (!model) return nullptr;
    model->scale.multiplyScalar(3);
    return std::make_shared<Tank>(model);
}