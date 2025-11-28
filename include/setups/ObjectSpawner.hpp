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
//TODO check this: REALLY UNSURE IF THIS IS WISE SINCE THIS INCREASES COUPLING
template<>
struct ObjectTraits<threepp::Human> {
    static constexpr bool hasAudio = true;
};
template<typename T>
class ObjectSpawner {
public:
    ObjectSpawner(std::shared_ptr<threepp::Scene> scene,
              const std::string &modelPath,
              int numObjects,
              threepp::AudioListener* listener = nullptr,
              const std::string &soundPath = "",
              ScoreManager* scoreManager = nullptr)
        : scene_(scene),
          modelPath_(modelPath),
          listener_(listener),
          soundPath_(soundPath),
          numObjects_(numObjects),
          scoreManager_(scoreManager),
          objectGroup_(threepp::Group::create()) {}


    void spawnObjects(CollisionManager &collisionManager) {
        threepp::AssimpLoader loader;
        auto baseModel = loader.load(modelPath_);
        if (!baseModel) return;

        for (int i = 0; i < numObjects_; ++i) {
            auto model = baseModel->clone();

            // Choose a correct creation path depending on if i want it to use audio or not
            std::shared_ptr<T> obj;
            if constexpr (ObjectTraits<T>::hasAudio) {
                // only Humans use sound and since this is already created i also use it for scores
                obj = T::create(model, listener_, soundPath_, scoreManager_);
            } else {
                // All other objects use normal creation
                obj = T::create(model);
            }

            obj->setRandomPosition(-50.0f, 50.0f, -50.0f, 50.0f);
            collisionManager.registerCollidable(obj.get());
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
    threepp::AudioListener* listener_;
    std::string soundPath_;
    int numObjects_;
    std::shared_ptr<threepp::Group> objectGroup_;
    std::vector<std::shared_ptr<T> > objects_;
    ScoreManager* scoreManager_;
};

#endif // CARGAME_OBJECTSPAWNER_HPP
