//
// Created by evest on 09.10.2025.
//

#ifndef CARGAME_COLLISION_HPP
#define CARGAME_COLLISION_HPP

class CollisionObject {
public:
    bool isColliding(const CollisionObject &other) const {
        return (position_.x <= other.position_.x + other.size_.x &&
                position_.x + size_.x > other.position_.x &&
                position_.y <= other.position_.y + other.size_.y &&
                position_.y + size_.y > other.position_.y &&
                position_.z <= other.position_.z + other.size_.z &&
                position_.z + size_.z > other.position_.z);

    }

protected:
    threepp::Vector3 position_;
    threepp::Vector3 size_;
};
#endif //CARGAME_COLLISION_HPP