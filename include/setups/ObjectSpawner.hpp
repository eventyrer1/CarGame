#ifndef CARGAME_OBJECTSPAWNER_HPP
#define CARGAME_OBJECTSPAWNER_HPP

#include "threepp/threepp.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include "collision/CollisionManager.hpp"
#include <memory>
#include <vector>

template<typename T>
class ObjectSpawner {
public:
    ObjectSpawner(std::shared_ptr<threepp::Scene> scene,
                  const std::string& modelPath,
                  int numObjects)
        : scene_(scene), modelPath_(modelPath), numObjects_(numObjects),
          objectGroup_(threepp::Group::create()) {}

    void spawnObjects(CollisionManager& collisionManager) {
        threepp::AssimpLoader loader;
        auto baseModel = loader.load(modelPath_);
        if (!baseModel) return;

        for (int i = 0; i < numObjects_; ++i) {
            auto model = baseModel->clone();
            auto obj = T::create(model);
            obj->setRandomPosition(-50.0f, 50.0f, -50.0f, 50.0f);

            collisionManager.registerCollidable(obj.get());
            objects_.emplace_back(obj);
            objectGroup_->add(obj);
        }
        scene_->add(objectGroup_);
    }

    std::shared_ptr<threepp::Group> getGroup() const { return objectGroup_; }
    const std::vector<std::shared_ptr<T>>& getObjects() const { return objects_; }

private:
    std::shared_ptr<threepp::Scene> scene_;
    std::string modelPath_;
    int numObjects_;
    std::shared_ptr<threepp::Group> objectGroup_;
    std::vector<std::shared_ptr<T>> objects_;
};

#endif // CARGAME_OBJECTSPAWNER_HPP
