#ifndef CARGAME_HUMAN_HPP
#define CARGAME_HUMAN_HPP

#include "SpawnableObject.hpp"
#include "threepp/audio/Audio.hpp"

class Car;
class ScoreManager;

namespace threepp {

    class Human : public SpawnableObject {
    public:
        Human(std::shared_ptr<Object3D> model,
              AudioListener* listener,
              const std::vector<std::string>& soundPaths,
              ScoreManager* scoreManager);

        static std::shared_ptr<Human> create(std::shared_ptr<Object3D> model,
                                             AudioListener* listener,
                                             const std::vector<std::string>& soundPaths,
                                             ScoreManager* scoreManager);

        void computeBoundingBox() override;
        void onCollision(::Collidable* other) override;
        void reset(float minX, float maxX, float minZ, float maxZ);
        void collideWith(Car& car) override;

        bool isConsumed() const { return hit_; }

    private:
        AudioListener* listener_ = nullptr;                         // ← REQUIRED
        std::shared_ptr<threepp::PositionalAudio> collisionSound_;
        bool hit_ = false;
        ScoreManager* scoreManager_ = nullptr;

        std::vector<std::string> soundPaths_;                       // ← CORRECT

        void handleCollisionResponse(Collidable* other);
    };

}

#endif
