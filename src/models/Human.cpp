#include "models/Human.hpp"


using namespace threepp;

Human::Human(std::shared_ptr<Object3D> model, AudioListener& listener){
    collisionSound_ = std::make_shared<threepp::PositionalAudio>(listener, "Data/Sounds/Splat.waw");
    Object3D::add(*collisionSound_);
}


std::shared_ptr<Human> Human::create(std::shared_ptr<Object3D> model, AudioListener& listener) {
    if (model) {
        auto human = std::make_shared<Human>(model, listener);
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
    if(collisionSound_ && !collisionSound_->isPlaying()){
        collisionSound_->play();
    }
}