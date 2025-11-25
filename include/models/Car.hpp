// include/models/Car.hpp
#ifndef CAR_HPP
#define CAR_HPP

#include <memory>

#include "SpawnableObject.hpp"
#include "threepp/threepp.hpp"
#include "collision/Collidable.hpp"
#include "keyListeners/InterfaceCarKeyListener.hpp"
#include <opencv2/opencv.hpp>

using namespace threepp;

class Car : public SpawnableObject {
public:
    explicit Car(std::shared_ptr<Object3D> model);

    static std::shared_ptr<Car> create(const std::filesystem::path &path);

    void update(double deltaTime, const CarActions::Move move, const CarActions::Turn turn);

    PerspectiveCamera &camera();

    static std::shared_ptr<Car> createDummyCar() {
        return std::make_shared<Car>(nullptr);
    }
    void onCollision(Collidable *other) override;

    void reset();

    //----- Getters -----
    float getSpeed() const { return speed_; }
    float getMaxSpeed() const { return maxSpeed_; }
    float getAcceleration() const { return acceleration_; }
    float getRotationSpeed() const { return rotationSpeed_; }
    float getDrag() const { return drag_; }
    //----- Setters -----
    void setSpeed(float v) { speed_ = v; }
    void setMaxSpeed(float v) { maxSpeed_ = v; }
    void setAcceleration(float v) { acceleration_ = v; }
    void setRotationSpeed(float v) { rotationSpeed_ = v; }
    void setDrag(float v) { drag_ = v; }

private:
    float speed_ = 0;
    float maxSpeed_ = 30;
    float acceleration_ = 5;
    float rotationSpeed_ = 0.5;
    float angle_ = 0.0;
    float drag_ = 10.f;
    bool visionEnabled_ = false;

    std::unique_ptr<PerspectiveCamera> camera_;

    std::shared_ptr<Mesh> boundingSphereHelper_;
    Scene *scene_ = nullptr;

    void updateBoundingSphere();

    void handleCollisionResponse(Collidable *other);
};

#endif // CAR_HPP
