#ifndef CARGAME_WORLDOBJECT_HPP
#define CARGAME_WORLDOBJECT_HPP

#include "threepp/threepp.hpp"
#include "collision/Collidable.hpp"
#include "setups/BoundingBoxHelper.hpp" //this has to be here
#include <memory>
#include <random>

namespace threepp {

    class SpawnableObject : public Collidable {
    public:

       virtual void setRandomPosition(float minX, float maxX, float minZ, float maxZ);


    protected:
        explicit SpawnableObject(std::shared_ptr<threepp::Scene> scene = nullptr)
     : scene_(std::move(scene)) {}

        std::weak_ptr<threepp::Scene> scene_;

        std::shared_ptr<Object3D> visualBounds_;
};

}

#endif // CARGAME_WORLDOBJECT_HPP
