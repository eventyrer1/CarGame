#include "TreeManager.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include <random>

namespace threepp {
    TreeManager::TreeManager(std::shared_ptr<Scene> scene,
                             const std::string &modelPath,
                             int numTrees)
        : scene_(scene),
          treeModelPath_(modelPath),
          numTrees_(numTrees),
          treeGroup_(Group::create()) {
    }

    void TreeManager::spawnTrees() {
        AssimpLoader loader;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distX(-50.0f, 50.0f);
        std::uniform_real_distribution<float> distZ(-50.0f, 50.0f);

        auto model = loader.load(treeModelPath_);

        if (model) {
            for (int i = 0; i < numTrees_; ++i) {

                // Set random position
                model->position.set(distX(gen), 0.0f, distZ(gen));
                trees_.emplace_back(Tree::create((model->clone())));
                treeGroup_->add(trees_.back());
            }
            scene_->add(treeGroup_);
        }

    }

    std::shared_ptr<Group> TreeManager::getTreeGroup() const {
        return treeGroup_;
    }

    const std::vector<std::shared_ptr<Tree>> &TreeManager::getTrees() const {
        return trees_;
    }
} // namespace threepp
