#ifndef CARGAME_HUMAN_HPP
#define CARGAME_HUMAN_HPP

#include "SpawnableObject.hpp"
#include "threepp/audio/Audio.hpp"

class Car;
class ScoreManager;

namespace threepp {
    class Human : public SpawnableObject {
    public:
        Human(const std::shared_ptr<Object3D> &model,
              std::shared_ptr<threepp::Scene> scene,
              const std::shared_ptr<threepp::AudioListener> &listener,
              const std::vector<std::string> &soundPaths,
              const std::shared_ptr<ScoreManager> &scoreManager);

        static std::shared_ptr<Human> create(std::shared_ptr<Object3D> model,
                                             std::shared_ptr<threepp::Scene> scene,
                                             std::shared_ptr<threepp::AudioListener> listener,
                                             const std::vector<std::string> &soundPaths,
                                             std::shared_ptr<ScoreManager> scoreManager);

        void computeBoundingBox() override;

        void onCollision(const std::shared_ptr<::Collidable>& other) override;

        void reset(float minX, float maxX, float minZ, float maxZ);

        void collideWith(Car &car) override;

        bool isConsumed() const { return hit_; }

    private:
        std::shared_ptr<threepp::AudioListener> listener_;
        std::shared_ptr<threepp::PositionalAudio> collisionSound_;
        bool hit_ = false;
        std::shared_ptr<ScoreManager> scoreManager_;

        std::vector<std::string> soundPaths_; // ← CORRECT

        void handleCollisionResponse(const std::shared_ptr<Collidable>& other);
    };
}

#endif
