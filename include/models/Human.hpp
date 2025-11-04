//
// Created by evest on 04.11.2025.
//

#ifndef CARGAME_HUMAN_HPP
#define CARGAME_HUMAN_HPP
#include "SpawnableObject.hpp"

namespace threepp {

    class Human : public SpawnableObject {
    public:
        Human(std::shared_ptr<Object3D> model);
        using SpawnableObject::SpawnableObject;
        static std::shared_ptr<Human> create(std::shared_ptr<Object3D> model);
        void computeBoundingBox() override;
    };

}
#endif //CARGAME_HUMAN_HPP