#include "collision/CollisionManager.hpp"
#include <algorithm>


void CollisionManager::registerCollidable(const std::shared_ptr<Collidable> &object) {
    if (!object) {
        return;
    }

    collidables_.erase(std::remove_if(collidables_.begin(), collidables_.end(), [](const auto &weakPtr) {
        return weakPtr.expired();
    }), collidables_.end());

    const auto alreadyRegistered = std::find_if(collidables_.begin(), collidables_.end(), [&](const auto &weakPtr) {
        auto locked = weakPtr.lock();
        return locked && locked.get() == object.get();
    });

    if (alreadyRegistered == collidables_.end()) {
        collidables_.push_back(object);
    }
}


void CollisionManager::checkCollisions() {
    collidables_.erase(std::remove_if(collidables_.begin(), collidables_.end(), [](const auto &weakPtr) {
        return weakPtr.expired();
    }), collidables_.end());

    for (size_t i = 0; i < collidables_.size(); ++i) {
        auto first = collidables_[i].lock();
        if (!first) continue;

        for (size_t j = i + 1; j < collidables_.size(); ++j) {

            auto second = collidables_[j].lock();
            if (!second) continue;

            if (first->checkCollision(*second)) {
                // Notify both objects that they have collided
                first->onCollision(second);
                second->onCollision(first);
            }
        }
    }
}


std::vector<std::shared_ptr<Collidable>> CollisionManager::getCollisions(const std::shared_ptr<Collidable>& object) const {
    std::vector<std::shared_ptr<Collidable>> collisions;
    if (!object) {
        return collisions;
    }

    for (const auto &weakOther: collidables_) {
        auto other = weakOther.lock();
        if (!other || other == object) continue;

        if (object->checkCollision(*other)) {
            collisions.push_back(other);
        }
    }
    return collisions;
}