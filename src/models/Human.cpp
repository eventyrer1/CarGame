#include "models/Human.hpp"
#include "BoundingBoxHelper.hpp"
#include <threepp/materials/MeshBasicMaterial.hpp>
#include <threepp/materials/MeshLambertMaterial.hpp>
#include <threepp/materials/MeshPhongMaterial.hpp>
#include <threepp/materials/MeshStandardMaterial.hpp>


using namespace threepp;

Human::Human(std::shared_ptr<Object3D> model, AudioListener& listener, const std::string& soundPath){
    if (model) {
        // Copy the provided model graph into this Object3D so transforms/materials live on this instance
        this->copy(*model);
    }
    // Create positional audio for collision
    try {
        collisionSound_ = std::make_shared<threepp::PositionalAudio>(listener, soundPath);
        Object3D::add(*collisionSound_);
    } catch (...) {
        // Fallback: ignore audio issues
        collisionSound_.reset();
    }
}


std::shared_ptr<Human> Human::create(std::shared_ptr<Object3D> model, AudioListener& listener, const std::string& soundPath) {
    if (model) {
        auto human = std::make_shared<Human>(model, listener, soundPath);
        human->updateMatrixWorld(true);
        human->computeBoundingBox();
        human->ensureUniqueMaterials();
        return human;
    }
    return nullptr;
}

void Human::computeBoundingBox() {
    updateMatrixWorld(true);
    collisionBox_ = std::make_optional<Box3>(BoundingBoxHelper::computeCollisionBox(*this));
}

void Human::onCollision(Collidable* other) {
    handleCollisionResponse(other);

}

void Human::handleCollisionResponse(Collidable* /*other*/) {
    // Play splat sound once per collision
    if(collisionSound_ && !collisionSound_->isPlaying()){
        collisionSound_->play();
    }
    // Visual feedback: tint all meshes red
    setColorAllMeshes(Color::red);
}

void Human::ensureUniqueMaterials() {
    traverse([&](Object3D& obj){
        if (auto mesh = obj.as<Mesh>()) {
            auto mat = mesh->material();
            if (mat) {
                // clone to avoid sharing the same material among instances
                mesh->setMaterial(mat->clone());
            }
        }
    });
}

void Human::setColorAllMeshes(const Color& c) {
    traverse([&](Object3D& obj){
        if (auto mesh = obj.as<Mesh>()) {
            auto mat = mesh->material();
            if (!mat) return;
            if (auto basic = mat->as<MeshBasicMaterial>()) {
                basic->color = c;
            } else if (auto lambert = mat->as<MeshLambertMaterial>()) {
                lambert->color = c;
            } else if (auto phong = mat->as<MeshPhongMaterial>()) {
                phong->color = c;
            } else if (auto standard = mat->as<MeshStandardMaterial>()) {
                standard->color = c;
            }
        }
    });
}