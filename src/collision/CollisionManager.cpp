
#include "collision/CollisionManager.hpp"
#include <algorithm>

void CollisionManager::registerCollidable(Collidable* object) {
    if (object && std::find(collidables_.begin(), collidables_.end(), object) == collidables_.end()) {
        collidables_.push_back(object);
    }
}



void CollisionManager::checkCollisions() {
    for (size_t i = 0; i < collidables_.size(); ++i) {
        for (size_t j = i + 1; j < collidables_.size(); ++j) {
            if (collidables_[i]->checkCollision(*collidables_[j])) {
                // Notify both objects that they have collided
                collidables_[i]->onCollision(collidables_[j]);
                collidables_[j]->onCollision(collidables_[i]);
            }
        }
    }
}



std::vector<Collidable*> CollisionManager::getCollisions(Collidable* object) const {
    std::vector<Collidable*> collisions;
    for (auto* other : collidables_) {
        if (other != object && object->checkCollision(*other)) {
            collisions.push_back(other);
        }
    }
    return collisions;
}

