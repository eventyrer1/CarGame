#ifndef CARGAME_HUMAN_HPP
#define CARGAME_HUMAN_HPP

#include "SpawnableObject.hpp"

namespace threepp {

    class Human : public SpawnableObject {
    public:
        Human(std::shared_ptr<Object3D> model);
        using SpawnableObject::SpawnableObject;
        static std::shared_ptr<Human> create(std::shared_ptr<Object3D> model);
        void computeBoundingBox() override;
        void onCollision(::Collidable* other) override;

    private:

        void handleCollisionResponse(Collidable *other);
    };

}
#endif //CARGAME_HUMAN_HPP