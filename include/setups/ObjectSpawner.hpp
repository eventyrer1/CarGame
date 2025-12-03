#ifndef CARGAME_OBJECTSPAWNER_HPP
#define CARGAME_OBJECTSPAWNER_HPP

#include "threepp/threepp.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include "collision/CollisionManager.hpp"
#include "models/Human.hpp"
#include "threepp/audio/Audio.hpp"
#include "setups/ScoreManager.hpp"
#include <memory>
#include <vector>

template<typename T>
struct ObjectTraits {
    static constexpr bool hasAudio = false;
};


template<>
struct ObjectTraits<threepp::Human> {
    static constexpr bool hasAudio = true;
};

template<typename T>
class ObjectSpawner {
public:
    ObjectSpawner(std::shared_ptr<threepp::Scene> const scene,
                  const std::string &modelPath,
                  int numObjects,
                  float minX, float maxX,
                  float minZ, float maxZ,
                  std::shared_ptr<threepp::AudioListener> const listener = nullptr,
                  const std::vector<std::string> &soundPaths = {},

                  std::shared_ptr<ScoreManager> const scoreManager = nullptr)
        : scene_(scene),
          modelPath_(modelPath),
          listener_(listener),
          soundPaths_(soundPaths),
          numObjects_(numObjects),
          scoreManager_(scoreManager),
          minX_(minX),
          maxX_(maxX),
          minZ_(minZ),
          maxZ_(maxZ),
          objectGroup_(threepp::Group::create()) {
    }


    void spawnObjects(CollisionManager &collisionManager) {
        threepp::AssimpLoader loader;
        auto baseModel = loader.load(modelPath_);
        if (!baseModel) return;

        for (int i = 0; i < numObjects_; ++i) {
            auto model = baseModel->clone();

            // Choose a correct creation path depending on if i want it to use audio or not
            std::shared_ptr<T> obj;
            if constexpr (ObjectTraits<T>::hasAudio) {
                // only Humans use sound, and since this is already created I also use it for scores
                obj = T::create(model, scene_, listener_, soundPaths_, scoreManager_);

            } else {
                // All other objects use normal creation
                obj = T::create(model, scene_);

            }

            obj->setRandomPosition(minX_, maxX_, minZ_, maxZ_);
            collisionManager.registerCollidable(obj);
            objects_.emplace_back(obj);
            objectGroup_->add(obj);
        }

        scene_->add(objectGroup_);
    }

    std::shared_ptr<threepp::Group> getGroup() const { return objectGroup_; }
    const std::vector<std::shared_ptr<T> > &getObjects() const { return objects_; }

private:
    std::shared_ptr<threepp::Scene> scene_;
    std::string modelPath_;
    std::shared_ptr<threepp::AudioListener> listener_;
    std::vector<std::string> soundPaths_;

    int numObjects_;
    std::shared_ptr<threepp::Group> objectGroup_;
    std::vector<std::shared_ptr<T> > objects_;
    std::shared_ptr<ScoreManager> scoreManager_;
    float minX_;
    float maxX_;
    float minZ_;
    float maxZ_;
};

#endif // CARGAME_OBJECTSPAWNER_HPP
