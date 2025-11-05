#ifndef CARGAME_HUMAN_HPP
#define CARGAME_HUMAN_HPP

#include "SpawnableObject.hpp"
#include "threepp/audio/Audio.hpp"

namespace threepp {

    class Human : public SpawnableObject {
    public:
        Human(std::shared_ptr<Object3D> model, AudioListener& listener);        using SpawnableObject::SpawnableObject;
        static std::shared_ptr<Human> create(std::shared_ptr<Object3D> model, AudioListener& listener);
        void computeBoundingBox() override;
        void onCollision(::Collidable* other) override;

    private:
        std::shared_ptr<PositionalAudio> collisionSound_;
        void handleCollisionResponse(Collidable *other);
    };

}
#endif //CARGAME_HUMAN_HPP