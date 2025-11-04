#pragma once
#include <threepp/threepp.hpp>

using namespace threepp;

class BoundingBoxHelper {
public:

    // Generic world-space bounding box
    static Box3 computeBoundingBox(Object3D& object) {
        object.updateMatrixWorld(true);
        Box3 box;
        box.setFromObject(object);
        return box;
    }

    // Custom collision box for trees that only makes a hitbox that is 5 units tall
    static Box3 computeCollisionBox(Object3D& object, float height = 5.0f, float shrinkXZ = 0.5f) {
        object.updateMatrixWorld(true);

        Box3 fullBox;
        fullBox.setFromObject(object);


        return fullBox;
    }

    static Sphere computeBoundingSphere(Object3D& object, float radiusScale = 1.0f) {
        Box3 box = computeBoundingBox(object);
        Sphere sphere;
        box.getBoundingSphere(sphere);
        sphere.radius *= radiusScale;
        return sphere;
    }

    static void updateBoundingBox(Object3D& object, Box3& box) {
        box.setFromObject(object);
    }

    static std::shared_ptr<Box3Helper> createHelper(const Box3& box, const Color& color = Color::green) {
        return Box3Helper::create(box, color);
    }
};
