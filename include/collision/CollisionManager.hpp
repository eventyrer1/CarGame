#pragma once

#include "collidable.hpp"
#include <vector>

#include <functional>

/**
 * Manages collision detection and responses for all collidable objects
 */
class CollisionManager {
public:
    using CollisionCallback = std::function<void(Collidable*, Collidable*)>;

    // Register objects for collision detection
    void registerCollidable(Collidable* object);
    void unregisterCollidable(Collidable* object);

    // Check all collisions and trigger callbacks
    void checkCollisions();

    // Set global collision callback (optional)
    void setCollisionCallback(CollisionCallback callback);

    // Get all objects colliding with a specific object
    std::vector<Collidable*> getCollisions(Collidable* object) const;

private:
    std::vector<Collidable*> collidables_;
    CollisionCallback collisionCallback_;

    bool checkCollisionPair(const Collidable& a, const Collidable& b) const;
};
