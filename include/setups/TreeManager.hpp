#pragma once

#include "threepp/threepp.hpp"
#include "models/Tree.hpp"  // ADDED: Include Tree header
#include <memory>
#include <vector>
#include "collision/CollisionManager.hpp"



class TreeManager {
public:
    TreeManager(std::shared_ptr<Scene> scene,
                const std::string& modelPath,
                int numTrees);

    void spawnTrees(CollisionManager& collisionManager);

    std::shared_ptr<threepp::Group> getTreeGroup() const;
    const std::vector<std::shared_ptr<threepp::Tree>>& getTrees() const; // CHANGED: threepp::Tree

private:
    std::shared_ptr<threepp::Scene> scene_;
    std::string treeModelPath_;
    int numTrees_;
    std::shared_ptr<threepp::Group> treeGroup_;
    std::vector<std::shared_ptr<threepp::Tree>> trees_; // CHANGED: threepp::Tree
};