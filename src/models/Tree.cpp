#include "setups/TreeManager.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include "models/Tree.hpp"
#include <random>

namespace threepp {
    Tree::Tree(std::shared_ptr<Object3D> model) {
        if (model) {
            add(model);
        }
    }

    std::shared_ptr<Tree> Tree::create(std::shared_ptr<Object3D> model) {
        if (!model) return nullptr;
        model->scale.multiplyScalar(501.0f);
        return std::make_shared<Tree>(model);

    }
// rng was recommended by Jon aksel
    void Tree::setRandomPosition(float minX, float maxX, float minZ, float maxZ) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distX(minX, maxX);
        std::uniform_real_distribution<float> distZ(minZ, maxZ);

        position.set(distX(gen), 0.0f, distZ(gen));
        position_ = position;
        size_ = { 0.2, 0.3, 0.2 };
    }
}
