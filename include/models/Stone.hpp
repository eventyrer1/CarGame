//
// Created by evest on 27.11.2025.
//
#ifndef CARGAME_STONE_HPP
#define CARGAME_STONE_HPP

#include "SpawnableObject.hpp"

namespace threepp {

    class Stone : public SpawnableObject {
    public:
        Stone(std::shared_ptr<Object3D> model);
        using SpawnableObject::SpawnableObject;
        static std::shared_ptr<Stone> create(std::shared_ptr<Object3D> model);
        void computeBoundingBox() override;
    };

} // namespace threepp

#endif
