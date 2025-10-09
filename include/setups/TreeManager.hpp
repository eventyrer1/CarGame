#ifndef TREEMANAGER_HPP
#define TREEMANAGER_HPP

#include "threepp/threepp.hpp"
#include <memory>
#include <string>
#include "models/Tree.hpp"

namespace threepp {

    class TreeManager {
    public:
        TreeManager(std::shared_ptr<Scene> scene, const std::string& modelPath, int numTrees);

        void spawnTrees();
        std::shared_ptr<Group> getTreeGroup() const;
        const std::vector<std::shared_ptr<Tree>> &getTrees() const;

    private:
        std::shared_ptr<Scene> scene_;  // <- must match constructor
        std::shared_ptr<Group> treeGroup_;
        std::string treeModelPath_;
        int numTrees_;
        std::vector<std::shared_ptr<Tree>> trees_;
    };

} // namespace threepp

#endif // TREEMANAGER_HPP
