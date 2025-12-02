
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

    static Box3 computeCollisionBox(Object3D& object, float height = 5.0f, float shrinkXZ = 0.5f) {
        object.updateMatrixWorld(true);
        Box3 fullBox;
        fullBox.setFromObject(object);
        Vector3 min = fullBox.min();
        Vector3 max = fullBox.max();
        Vector3 center = (min + max) * 0.5f;
        Vector3 size = max - min;
        float halfX = (size.x * 0.5f) * std::max(0.0f, 1.0f - shrinkXZ);
        float halfZ = (size.z * 0.5f) * std::max(0.0f, 1.0f - shrinkXZ);
        float halfY = std::min(size.y * 0.5f, height * 0.5f);
        Vector3 newMin = center - Vector3{halfX, halfY, halfZ};
        Vector3 newMax = center + Vector3{halfX, halfY, halfZ};
        Box3 box;
        box.set(newMin, newMax);
        return box;
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


};
