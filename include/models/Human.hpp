#ifndef CARGAME_HUMAN_HPP
#define CARGAME_HUMAN_HPP

#include "SpawnableObject.hpp"
#include "threepp/audio/Audio.hpp"
class Car; // forward

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
        void onCollision(::Collidable *other) override; // generic visual flatten
        void reset(float minX, float maxX, float minZ, float maxZ);

        // Double-dispatch handler for Car power-up consumption
        void collideWith(Car& car) override;
        bool isConsumed() const { return hit_; }
    private:
        std::shared_ptr<PositionalAudio> collisionSound_;
        bool hit_ = false;
        void handleCollisionResponse(Collidable *other);
    };
}

#endif // CARGAME_HUMAN_HPP
