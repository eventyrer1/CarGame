
#include "../../include/collision/CollisionManager.hpp"
#include <algorithm>

void CollisionManager::registerCollidable(Collidable* object) {
    if (object && std::find(collidables_.begin(), collidables_.end(), object) == collidables_.end()) {
        collidables_.push_back(object);
    }
}

void CollisionManager::unregisterCollidable(Collidable* object) {
    collidables_.erase(
        std::remove(collidables_.begin(), collidables_.end(), object),
        collidables_.end()
    );
}

void CollisionManager::checkCollisions() {
    for (size_t i = 0; i < collidables_.size(); ++i) {
        for (size_t j = i + 1; j < collidables_.size(); ++j) {
            if (checkCollisionPair(*collidables_[i], *collidables_[j])) {
                // Notify both objects
                collidables_[i]->onCollision(collidables_[j]);
                collidables_[j]->onCollision(collidables_[i]);

                // Call global callback if set
                if (collisionCallback_) {
                    collisionCallback_(collidables_[i], collidables_[j]);
                }
            }
        }
    }
}

void CollisionManager::setCollisionCallback(CollisionCallback callback) {
    collisionCallback_ = std::move(callback);
}

std::vector<Collidable*> CollisionManager::getCollisions(Collidable* object) const {
    std::vector<Collidable*> collisions;
    for (auto* other : collidables_) {
        if (other != object && checkCollisionPair(*object, *other)) {
            collisions.push_back(other);
        }
    }
    return collisions;
}

bool CollisionManager::checkCollisionPair(const Collidable& a, const Collidable& b) const {
    // Sphere vs Box collision
    if (a.getSphere() && b.getBox()) {
        return a.getSphere()->intersectsBox(*b.getBox());
    }
    if (a.getBox() && b.getSphere()) {
        return b.getSphere()->intersectsBox(*a.getBox());
    }

    // Sphere vs Sphere collision
    if (a.getSphere() && b.getSphere()) {
        return a.getSphere()->intersectsSphere(*b.getSphere());
    }

    // Box vs Box collision
    if (a.getBox() && b.getBox()) {
        return a.getBox()->intersectsBox(*b.getBox());
    }

    return false;
}
