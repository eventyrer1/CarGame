#pragma once
#include <threepp/threepp.hpp>

using namespace threepp;

class Collidable : public Object3D, public std::enable_shared_from_this<Collidable> {
public:

    // Generic world-space bounding box
     virtual void computeBoundingBox() {
        updateMatrixWorld(true);
        collisionBox_ = std::make_optional<Box3>();
        collisionBox_.value().setFromObject(*this);
    }

    // Custom collision box for trees that only makes a hitbox that is 5 units tall
     virtual void computeBoundingSphere(float radiusScale = 1.0f) {
         computeBoundingBox();
         boundingSphere_ = std::make_optional<Sphere>();
         collisionBox_.value().getBoundingSphere(boundingSphere_.value());
         boundingSphere_.value().radius *= radiusScale;
    }

    virtual void onCollision(Collidable* other) {};


    virtual bool checkCollision(const Collidable& other) const {

         if (other.boundingSphere_.has_value()) {
             if (boundingSphere_.has_value()) {
                 return other.boundingSphere_.value().intersectsSphere(boundingSphere_.value());
             } else {
                return other.boundingSphere_.value().intersectsBox(collisionBox_.value());
             }
         }
         else if (other.collisionBox_.has_value()) {
             if (boundingSphere_.has_value()) {
                 return other.collisionBox_.value().intersectsSphere(boundingSphere_.value());
             } else {
                 return other.collisionBox_.value().intersectsBox(collisionBox_.value());
             }
         }
         return false;
     }
    const std::optional<Box3>& getBox() const { return collisionBox_; }
    const std::optional<Sphere>& getSphere() const { return boundingSphere_; }

protected:
    std::optional<Box3> collisionBox_;
    std::optional<Sphere> boundingSphere_;
};
