#ifndef CAR_LOGIC_HPP
#define CAR_LOGIC_HPP

#include "keyListeners/CarActions.hpp"
#include "collision/Collidable.hpp"
#include "threepp/math/Vector3.hpp"

class CarLogic : public Collidable {
public:
    void update(double deltaTime, CarActions::Move move, CarActions::Turn turn);
    void reset();
    void onCollision(Collidable* other) override;

    float getSpeed() const { return speed_; }
    float getAngle() const { return angle_; }
    threepp::Vector3 getPosition() const { return position_; }

private:
    float speed_ = 0;
    float maxSpeed_ = 100;
    float acceleration_ = 100;
    float rotationSpeed_ = 2;
    float drag_ = 10;
    float angle_ = 0;
    threepp::Vector3 position_;

    void handleCollisionResponse(Collidable* other);
};

#endif
