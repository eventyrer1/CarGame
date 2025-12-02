#pragma once

#include "Collidable.hpp"
#include <vector>


/**
 * Manages collision detection and responses for all collidable objects
 */
class CollisionManager {
public:
    using CollisionCallback = std::function<void(Collidable*, Collidable*)>;

    // Register objects for collision detection
    void registerCollidable(Collidable* object);


    // Check all collisions and trigger callbacks
    void checkCollisions();


    // Get all objects colliding with a specific object
    std::vector<Collidable*> getCollisions(Collidable* object) const;

private:
    std::vector<Collidable*> collidables_;
    CollisionCallback collisionCallback_;


};
