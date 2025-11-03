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
    static Box3 computeTreeCollisionBox(Object3D& object, float height = 5.0f, float shrinkXZ = 0.5f) {
        object.updateMatrixWorld(true);

        Box3 fullBox;
        fullBox.setFromObject(object);

        // Copy min/max so we can safely modify
        Vector3 min = fullBox.min();
        Vector3 max = fullBox.max();

        Vector3 center;
        fullBox.getCenter(center);

        // Adjust height
        max.y = std::min(min.y + height, max.y);

        // Shrink horizontally
        Vector3 size;
        fullBox.getSize(size);

        float shrinkFactor = shrinkXZ * 0.9f; // 0.5 = shrink 50% from each side
        float dx = size.x * shrinkFactor;
        float dz = size.z * shrinkFactor;

        min.x += dx;
        max.x -= dx;
        min.z += dz;
        max.z -= dz;

        Box3 treeBox;
        treeBox.set(min, max);
        return treeBox;
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
