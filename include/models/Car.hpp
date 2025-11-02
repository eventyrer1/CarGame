// include/models/Car.hpp
#ifndef CAR_HPP
#define CAR_HPP

#include <memory>
#include "threepp/threepp.hpp"
#include "collision/Collidable.hpp"
#include "keyListeners/InterfaceCarKeyListener.hpp"
#include "keyListeners/CarActions.hpp"

using namespace threepp;

class Car : public Object3D, public Collidable {
public:
    explicit Car(std::shared_ptr<Object3D> model);
    static std::shared_ptr<Car> create(const std::filesystem::path& path);

    void update(double deltaTime, const CarActions::Move move, const CarActions::Turn turn);

    std::shared_ptr<Object3D> getModel() const { return model_; }
    PerspectiveCamera& camera();

    static std::shared_ptr<Car> createDummyCar() {
        return std::make_shared<Car>(nullptr);
    }

    Sphere getBoundingSphere() const { return boundingSphere_; }

    bool collidesWith(const Box3& otherBox) const { return boundingSphere_.intersectsBox(otherBox); }
    bool collidesWith(const Sphere& otherSphere) const { return boundingSphere_.intersectsSphere(otherSphere); }

    void setHitboxVisualization(bool enabled, Scene* scene = nullptr);
    void updateHitboxVisualization();

    bool checkCollision(const Collidable& other) const override;
    const Sphere* getSphere() const override { return &boundingSphere_; }
    Vector3 getPosition() const override { return model_ ? model_->position : Vector3(); }
    void onCollision(Collidable* other) override;
    void reset();


    float getSpeed() const { return speed_; }
    float getMaxSpeed() const { return maxSpeed_; }
    float getAcceleration() const { return acceleration_; }
    float getRotationSpeed() const { return rotationSpeed_; }
    float getDrag() const { return drag_; }


    void setSpeed(float v) { speed_ = v; }
    void setMaxSpeed(float v) { maxSpeed_ = v; }
    void setAcceleration(float v) { acceleration_ = v; }
    void setRotationSpeed(float v) { rotationSpeed_ = v; }
    void setDrag(float v) { drag_ = v; }

private:
    float speed_ = 0;
    float maxSpeed_ = 100;
    float acceleration_ = 100;
    float rotationSpeed_ = 2;
    float angle_ = 0.0;
    float drag_ = 10.f;

    std::shared_ptr<Object3D> model_;
    std::unique_ptr<PerspectiveCamera> camera_;

    Sphere boundingSphere_;
    std::shared_ptr<Mesh> boundingSphereHelper_;
    Scene* scene_ = nullptr;

    void updateBoundingSphere();
    void handleCollisionResponse(Collidable* other);
};

#endif // CAR_HPP
