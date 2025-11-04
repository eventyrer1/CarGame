#include "models/Human.hpp"


using namespace threepp;

Human::Human(std::shared_ptr<Object3D> model) {
    if (model) this->copy(*model);
}

std::shared_ptr<Human> Human::create(std::shared_ptr<Object3D> model) {
    if (model) {
        auto human = std::make_shared<Human>(model);
        human->updateMatrixWorld(true);
        human->computeBoundingBox();
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

void Human::handleCollisionResponse(Collidable* other) {
//do shit here bitch boy
}