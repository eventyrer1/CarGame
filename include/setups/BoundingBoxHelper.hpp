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


    static Box3 computeTreeCollisionBox(Object3D &object, float height=5.0f) {
        Box3 fullBox = computeBoundingBox(object);

        Vector3 center = getCenter(fullBox);
        Vector3 size = getSize(fullBox);


        
        Box3 treeBox;
        treeBox.set(
            //reduce max y since the branches of the tree makes the collision box way to big at the bottom
            Vector3(center.x, fullBox.min().y, center.z),
            Vector3(center.x, fullBox.min().y+height, center.z)
        );
        
        return treeBox;
    }


    static Sphere computeBoundingSphere(Object3D &object, float radiusScale = 1.0f) {
        Box3 box = computeBoundingBox(object);
        Sphere sphere;
        box.getBoundingSphere(sphere);
        

        sphere.radius *= radiusScale;
        
        return sphere;
    }


    static void updateBoundingSphere(Object3D &object, Sphere &sphere, float radiusScale = 1.0f) {
        sphere = computeBoundingSphere(object, radiusScale);
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