#pragma once

#include "threepp/threepp.hpp"

using namespace threepp;

/**
 * Interface for objects that can participate in collision detection
 */
class Collidable {
public:
    virtual ~Collidable() = default;

    // Check collision with another collidable
    virtual bool checkCollision(const Collidable& other) const = 0;

    // Get collision shape information
    virtual const Sphere* getSphere() const { return nullptr; }
    virtual const Box3* getBox() const { return nullptr; }

    // Get object position for collision response
    virtual Vector3 getPosition() const = 0;

    // Called when collision occurs
    virtual void onCollision(Collidable* other) = 0;
};
