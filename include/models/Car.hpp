// include/models/Car.hpp
#ifndef CAR_HPP
#define CAR_HPP

#include <memory>
#include "SpawnableObject.hpp"
#include "threepp/threepp.hpp"
#include "collision/Collidable.hpp"
#include "keyListeners/InterfaceCarKeyListener.hpp"
#include <opencv2/opencv.hpp>

class Car : public threepp::SpawnableObject {
public:
    explicit Car(std::shared_ptr<threepp::Object3D> model);
    static std::shared_ptr<Car> create(const std::filesystem::path &path);

    void update(double deltaTime, const CarActions::Move move, const CarActions::Turn turn);
    threepp::PerspectiveCamera &camera();
    static std::shared_ptr<Car> createDummyCar() { return std::make_shared<Car>(nullptr); }

    void onCollision(Collidable *other) override; // will delegate via double dispatch

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

    // Power-up API decoupled from Human implementation
    void applySpeedBoost(float amount, double durationSeconds);

private:
    float speed_ = 0;
    float maxSpeed_ = 150;
    float acceleration_ = 10;
    float rotationSpeed_ = 1.5;
    float angle_ = 0.0;
    float drag_ = 20.f;
    bool visionEnabled_ = false;

    std::unique_ptr<threepp::PerspectiveCamera> camera_;
    std::shared_ptr<threepp::Mesh> boundingSphereHelper_;
    threepp::Scene *scene_ = nullptr;

    // Power-up state
    double boostTimer_ = 0.0f;
    float originalMaxSpeed_ = 0.0f;
    float originalAcceleration_ = 0.0f;

    void updateBoundingSphere();
    void handleCollisionResponse(Collidable *other);
    void updateBoost(double dt);
};

#endif // CAR_HPP
