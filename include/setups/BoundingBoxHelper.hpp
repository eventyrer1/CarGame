#pragma once
//much AI was used here
#include <threepp/threepp.hpp>

using namespace threepp;

class BoundingBoxHelper {
public:

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

                        // Expand the global box-
                        box.union_(geometryBox);
                    }
                }
            }
        });

        return box;
    }

    // Add this new method for tree collision boxes
    static Box3 computeTreeCollisionBox(Object3D &object, float trunkRadiusFraction = 0.2f) {
        Box3 fullBox = computeBoundingBox(object);
        
        Vector3 center = getCenter(fullBox);
        Vector3 size = getSize(fullBox);
        
        // Reduce horizontal collision to trunk size
        float trunkRadius = std::max(size.x, size.z) * trunkRadiusFraction;
        
        Box3 treeBox;
        treeBox.set(
            Vector3(center.x - trunkRadius, fullBox.min().y, center.z - trunkRadius),
            Vector3(center.x + trunkRadius, fullBox.max().y, center.z + trunkRadius)
        );
        
        return treeBox;
    }

    static void updateBoundingBox(Object3D &object, Box3 &box) {
        box = computeBoundingBox(object);
    }

    static Vector3 getCenter(const Box3 &box) {
        Vector3 center;
        box.getCenter(center);
        return center;
    }

    static Vector3 getSize(const Box3 &box) {
        Vector3 size;
        box.getSize(size);
        return size;
    }

    static std::shared_ptr<Box3Helper> createHelper(const Box3 &box, const Color &color = Color::green) {
        return Box3Helper::create(box, color);
    }
};