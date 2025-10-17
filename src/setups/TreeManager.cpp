#include "TreeManager.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include <random>

using namespace threepp;

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

    auto baseModel = loader.load(treeModelPath_);

    if (baseModel) {
        for (int i = 0; i < numTrees_; ++i) {
            // Clone the model for each tree
            auto treeModel = baseModel->clone();

            // Create the tree first
            auto tree = Tree::create(treeModel);

            // Set random position using the tree's method
            tree->setRandomPosition(-50.0f, 50.0f, -50.0f, 50.0f);

            trees_.emplace_back(tree);
            treeGroup_->add(tree);
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