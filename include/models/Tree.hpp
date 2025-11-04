#ifndef CARGAME_TREE_HPP
#define CARGAME_TREE_HPP

#include "SpawnableObject.hpp"

namespace threepp {

    class Tree : public SpawnableObject {
    public:
        Tree(std::shared_ptr<Object3D> model);
        using SpawnableObject::SpawnableObject;
        static std::shared_ptr<Tree> create(std::shared_ptr<Object3D> model);
        void computeBoundingBox() override;
    };

} // namespace threepp

#endif // CARGAME_TREE_HPP
