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

       virtual void setRandomPosition(float minX, float maxX, float minZ, float maxZ);


    protected:
        SpawnableObject() = default;
        Scene* scene_ = nullptr;
        std::shared_ptr<Object3D> visualBounds_;
};

}

#endif // CARGAME_WORLDOBJECT_HPP
