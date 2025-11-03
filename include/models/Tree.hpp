
#ifndef CARGAME_TREE_HPP
#define CARGAME_TREE_HPP

#include "threepp/threepp.hpp"
#include "../collision/Collidable.hpp"
#include <memory>
#include <random>

namespace threepp {

    class Tree : public Object3D, public Collidable {  // CHANGED: inherit from Collidable
    public:
        explicit Tree(std::shared_ptr<Object3D> model, const Vector3& position = Vector3());
        static std::shared_ptr<Tree> create(std::shared_ptr<Object3D> model);
        void setRandomPosition(float minX, float maxX, float minZ, float maxZ);

        Box3 getBoundingBox() const { return collisionBox_; }
        bool collidesWith(const Box3& otherBox) const {
            return collisionBox_.intersectsBox(otherBox);
        }
        void setHitboxVisualization(bool enabled, Scene* scene = nullptr);
        void updateHitboxVisualization();
        
        // Implement Collidable interface
        bool checkCollision(const Collidable& other) const override;
        const Box3* getBox() const override { return &collisionBox_; }
        Vector3 getPosition() const override { return position; }
        void onCollision(Collidable* other) override;
        void updateCollisionBox();
    private:
        std::shared_ptr<Object3D> model_;
        Box3 collisionBox_;
        std::shared_ptr<Box3Helper> boundingBoxHelper_;
        Scene* scene_ = nullptr;
    };

} // namespace threepp

#endif //CARGAME_TREE_HPP