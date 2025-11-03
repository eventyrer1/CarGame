#include "models/SpawnableObject.hpp"
#include "BoundingBoxHelper.hpp"

using namespace threepp;

/*SpawnableObject::SpawnableObject(std::shared_ptr<Object3D> model, const Vector3& position) {

    add(shared_from_this());
    this->position.copy(position);
    computeBoundingBox();
}*/

/*std::shared_ptr<SpawnableObject> SpawnableObject::create(std::shared_ptr<Object3D> model) {
    if (!model) return nullptr;
    model->scale.multiplyScalar(1.0f);
    auto obj = std::make_shared<SpawnableObject>(model);
    obj->updateMatrixWorld(true);
    obj->updateCollisionBox();
    obj->updateHitboxVisualization();
    return obj;
}*/

void SpawnableObject::setRandomPosition(float minX, float maxX, float minZ, float maxZ) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(minX, maxX);
    std::uniform_real_distribution<float> distZ(minZ, maxZ);

    position.set(distX(gen), 0.0f, distZ(gen));

    updateMatrixWorld(true);
    computeBoundingBox();
    updateHitboxVisualization();
}

void SpawnableObject::setHitboxVisualization(bool enabled, Scene* scene) {
    scene_ = scene;
    if (enabled) {
        std::shared_ptr<BufferGeometry> geometry;
        std::shared_ptr<MeshBasicMaterial> material;

        if (boundingSphere_.has_value()) {
            auto sphere = boundingSphere_.value();
            geometry = SphereGeometry::create(sphere.radius, 30, 30, 1);
            material = MeshBasicMaterial::create(
                {{"color", Color::red},
                 {"wireframe", true}});
        } else {
            auto box = collisionBox_.value();
            geometry = BoxGeometry::create(box.getSize(), 1, 1, 1);material = MeshBasicMaterial::create(
                {{"color", Color::green},
                 {"wireframe", true}});
        }
        visualBounds_ = Mesh::create(geometry, material);
        scene->add(visualBounds_);
    } else {
        scene->remove(*visualBounds_);
        visualBounds_.reset();
    }
}

void SpawnableObject::updateHitboxVisualization() {
    if (visualBounds_) {
        visualBounds_->position = position;
    }
}
