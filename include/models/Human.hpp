#ifndef CARGAME_HUMAN_HPP
#define CARGAME_HUMAN_HPP

#include "SpawnableObject.hpp"
#include "threepp/audio/Audio.hpp"

namespace threepp {
    class Human : public SpawnableObject {
    public:
        Human(std::shared_ptr<Object3D> model,
              AudioListener *listener,
              const std::string &soundPath);
        static std::shared_ptr<Human> create(std::shared_ptr<Object3D> model,
                                             AudioListener *listener,
                                             const std::string &soundPath);
        void computeBoundingBox() override;
        void onCollision(::Collidable *other) override;

    private:
        std::shared_ptr<PositionalAudio> collisionSound_;
        bool hit_ = false;
        void handleCollisionResponse(Collidable *other);
    };
}

#endif // CARGAME_HUMAN_HPP
