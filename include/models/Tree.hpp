//
// Created by evest on 08.10.2025.
//

#ifndef CARGAME_TREE_HPP
#define CARGAME_TREE_HPP
#include "threepp/threepp.hpp"

#include <memory>
#include "Physics/Collision.hpp"


namespace threepp {

    class Tree : public Object3D, public CollisionObject {
    public:
        explicit Tree(std::shared_ptr<Object3D> model);

        static std::shared_ptr<Tree> create(std::shared_ptr<Object3D> model);

        // Optional: set a random position within a range
        void setRandomPosition(float minX, float maxX, float minZ, float maxZ);

    private:
    };
} // namespace threepp

#endif //CARGAME_TREE_HPP