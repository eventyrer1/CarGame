#ifndef CARGAME_WORLDOBJECT_HPP
#define CARGAME_WORLDOBJECT_HPP

#include "threepp/threepp.hpp"
#include "collision/Collidable.hpp"
#include "setups/BoundingBoxHelper.hpp"
#include <memory>
#include <random>

namespace threepp {

    class SpawnableObject : public Collidable {
    public:
        //explicit SpawnableObject(std::shared_ptr<Object3D> model, const Vector3& position = Vector3());
        //static std::shared_ptr<SpawnableObject> create(std::shared_ptr<Object3D> model);

       virtual void setRandomPosition(float minX, float maxX, float minZ, float maxZ);


       virtual void setHitboxVisualization(bool enabled, Scene* scene = nullptr);
       virtual void updateHitboxVisualization();

        // --- Collidable interface ---


        //void onCollision(Collidable* other) {}

       //virtual void updateCollisionBox();
    protected:
        SpawnableObject() = default;
        Scene* scene_ = nullptr;
        std::shared_ptr<Object3D> visualBounds_;
};

} // namespace threepp

#endif // CARGAME_WORLDOBJECT_HPP
