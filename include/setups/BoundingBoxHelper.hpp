#pragma once

#include <threepp/threepp.hpp>

using namespace threepp;

class BoundingBoxHelper {
public:
    /**
     * @brief Compute a world-space bounding box for an Object3D (including all meshes in its hierarchy).
     * @param object The root Object3D (can be a model, group, or single mesh).
     * @return A Box3 that encloses the full object in world coordinates.
     */
    static Box3 computeBoundingBox(Object3D &object) {
        Box3 box;
        box.makeEmpty();

        object.updateMatrixWorld(true); // ensure matrices are up-to-date

        object.traverse([&](Object3D &child) {
            if (auto mesh = dynamic_cast<Mesh *>(&child)) {
                if (mesh->geometry()) {
                    BufferGeometry &geometry = *mesh->geometry();

                    // Ensure geometry has a bounding box
                    geometry.computeBoundingBox();
                    if (geometry.boundingBox) {
                        Box3 geometryBox;
                        geometryBox.copy(*geometry.boundingBox);

                        // Transform local box into world space
                        geometryBox.applyMatrix4(*mesh->matrixWorld);

                        // Expand the global box - FIXED: use union_ instead of expandByObject
                        box.union_(geometryBox);
                    }
                }
            }
        });

        return box;
    }

    /**
     * @brief Update a Box3 to match the current position of an Object3D.
     *        Useful when the object moves or rotates.
     * @param object The Object3D to update from.
     * @param box The Box3 to modify.
     */
    static void updateBoundingBox(Object3D &object, Box3 &box) {
        box = computeBoundingBox(object);
    }

    /**
     * @brief Get the center of a Box3.
     */
    static Vector3 getCenter(const Box3 &box) {
        Vector3 center;
        box.getCenter(center);
        return center;
    }

    /**
     * @brief Get the size (width, height, depth) of a Box3.
     */
    static Vector3 getSize(const Box3 &box) {
        Vector3 size;
        box.getSize(size);
        return size;
    }

    /**
     * @brief Create a visible Box3Helper to visualize the bounding box in the scene.
     * @param box The Box3 to visualize.
     * @param color Optional color (default: green)
     * @return A shared_ptr<Box3Helper> that you can add to your scene.
     */
    static std::shared_ptr<Box3Helper> createHelper(const Box3 &box, const Color &color = Color::green) {
        return Box3Helper::create(box, color);
    }
};