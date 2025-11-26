#pragma once
#include <threepp/threepp.hpp>
#include <optional>

// Forward declaration to avoid circular include
class Car;

// Avoid using-directive in headers to reduce coupling/pollution.
class Collidable : public threepp::Object3D, public std::enable_shared_from_this<Collidable> {
public:
    // Generic world-space bounding box
    virtual void computeBoundingBox() {
        updateMatrixWorld(true);
        collisionBox_ = std::make_optional<threepp::Box3>();
        collisionBox_.value().setFromObject(*this);
    }

    // Generic bounding sphere optionally scaled
    virtual void computeBoundingSphere(float radiusScale = 1.0f) {
        computeBoundingBox();
        boundingSphere_ = std::make_optional<threepp::Sphere>();
        collisionBox_.value().getBoundingSphere(boundingSphere_.value());
        boundingSphere_.value().radius *= radiusScale;
    }

    // Single-dispatch collision notification (existing)
    virtual void onCollision(Collidable* /*other*/) {}

    // Double-dispatch entry point for Car-specific interactions.
    // Default no-op keeps low coupling: only classes that care override.
    virtual void collideWith(Car& /*car*/) {}

    virtual bool checkCollision(const Collidable& other) const {
        if (other.boundingSphere_.has_value()) {
            if (boundingSphere_.has_value()) {
                return other.boundingSphere_.value().intersectsSphere(boundingSphere_.value());
            }
            return other.boundingSphere_.value().intersectsBox(collisionBox_.value());
        }
        if (other.collisionBox_.has_value()) {
            if (boundingSphere_.has_value()) {
                return other.collisionBox_.value().intersectsSphere(boundingSphere_.value());
            }
            return other.collisionBox_.value().intersectsBox(collisionBox_.value());
        }
        return false;
    }

    const std::optional<threepp::Box3>& getBox() const { return collisionBox_; }
    const std::optional<threepp::Sphere>& getSphere() const { return boundingSphere_; }

protected:
    std::optional<threepp::Box3> collisionBox_;
    std::optional<threepp::Sphere> boundingSphere_;
};
