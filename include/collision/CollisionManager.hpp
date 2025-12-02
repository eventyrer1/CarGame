#pragma once
#include <functional>
#include <memory>
#include "Collidable.hpp"
#include <vector>


/**
 * Manages collision detection and responses for all collidable objects
 */
class CollisionManager {
public:
    using CollisionCallback = std::function<void(Collidable*, Collidable*)>;

    // Register objects for collision detection
    void registerCollidable(const std::shared_ptr<Collidable>& object);


    // Check all collisions and trigger callbacks
    void checkCollisions();


    // Get all objects colliding with a specific object
    std::vector<std::shared_ptr<Collidable>> getCollisions(const std::shared_ptr<Collidable>& object) const;
private:
    std::vector<std::weak_ptr<Collidable>> collidables_; //weak pointer was suggested by ai
    CollisionCallback collisionCallback_;


};
