#ifndef TANK_HPP
#define TANK_HPP

#include <memory>
#include "threepp/threepp.hpp"
#include "keylisteners/Car_keylistener.hpp"
#include "collision/Collidable.hpp"

using namespace threepp;

class Car : public Object3D, public Collidable {
public:
    explicit Car(std::shared_ptr<Object3D> model);

    static std::shared_ptr<Car> create(const std::filesystem::path &path);

    void update(double deltaTime,
                std::pair<CarKeyListener::CarActionMove, CarKeyListener::CarActionTurn> actions
    );

    std::shared_ptr<Object3D> getModel() const { return model_; }

    PerspectiveCamera &camera();

    static std::shared_ptr<Car> createDummyCar() {
        return std::make_shared<Car>(nullptr);
    }
    Sphere getBoundingSphere() const {
        return boundingSphere_;
    }


    bool collidesWith(const Box3& otherBox) const {
        return boundingSphere_.intersectsBox(otherBox);
    }


    bool collidesWith(const Sphere& otherSphere) const {
        return boundingSphere_.intersectsSphere(otherSphere);
    }


    void setHitboxVisualization(bool enabled, Scene* scene = nullptr);
    void updateHitboxVisualization();
    

    bool checkCollision(const Collidable& other) const override;
    const Sphere* getSphere() const override { return &boundingSphere_; }
    Vector3 getPosition() const override { return model_ ? model_->position : Vector3(); }
    void onCollision(Collidable* other) override;
    void resetPosition();

    //since this is only for testing and is very small i decided to have the entire getter and setter in the header
    float getSpeed() const { return speed_; }
    float getMaxSpeed() const { return maxSpeed_; }
    void setSpeed(float speed) { speed_ = speed; }

private:
    int speed_ = 10;
    int maxSpeed_ = 100;
    int acceleration_ = 100;
    int rotationSpeed_ = 2;
    float angle_ = 0.0;
    std::shared_ptr<Object3D> model_;
    std::unique_ptr<PerspectiveCamera> camera_;


    Sphere boundingSphere_;


    std::shared_ptr<Mesh> boundingSphereHelper_;
    Scene* scene_ = nullptr;

    void updateBoundingSphere();
    void handleCollisionResponse(Collidable* other);
};

#endif // TANK_HPP