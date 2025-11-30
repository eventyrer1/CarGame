#ifndef CAR_HPP
#define CAR_HPP

#include <memory>
#include "SpawnableObject.hpp"
#include "threepp/threepp.hpp"
#include "collision/Collidable.hpp"
#include "keyListeners/InterfaceCarKeyListener.hpp"
#include <opencv2/opencv.hpp>
#include <threepp/audio/Audio.hpp>

class Car : public SpawnableObject {

public:

    explicit Car(std::shared_ptr<Object3D> model, AudioListener *listener, const std::string &audioPath);
    static std::shared_ptr<Car> create(const std::filesystem::path &path, AudioListener *listener, const std::string &audioPath);

    void update(double deltaTime, const CarActions::Move move, const CarActions::Turn turn);
    PerspectiveCamera &camera();
    static std::shared_ptr<Car> createDummyCar() { return std::make_shared<Car>(nullptr, nullptr, ""); }

    void onCollision(Collidable *other) override;
    void reset();

    // ----- Getters -----
    float getSpeed() const { return speed_; }
    float getMaxSpeed() const { return maxSpeed_; }
    float getAcceleration() const { return acceleration_; }
    float getRotationSpeed() const { return rotationSpeed_; }
    float getDrag() const { return drag_; }

    // ----- Setters -----
    void setSpeed(float v) { speed_ = v; }
    void setMaxSpeed(float v) { maxSpeed_ = v; }
    void setAcceleration(float v) { acceleration_ = v; }
    void setRotationSpeed(float v) { rotationSpeed_ = v; }
    void setDrag(float v) { drag_ = v; }

    void applySpeedBoost(float amount, double durationSeconds);


Vector3 getForwardVector() const;
   Vector3 getRightVector() const;
 Vector3 getSensorOrigin() const;

    // Raycast callback (correct namespace)
    void setRaycastFunction(
        const std::function<float(const Vector3&,
                                  const Vector3&,
                                  float)>& fn)
    {
        raycastFunc_ = fn;
    }

private:

    float speed_ = 0;
    float maxSpeed_ = 150;
    float acceleration_ = 10;
    float rotationSpeed_ = 1.5;
    float angle_ = 0.0;
    float drag_ = 20.f;

    bool visionEnabled_ = false;

    std::unique_ptr<PerspectiveCamera> camera_;
    std::shared_ptr<Mesh> boundingSphereHelper_;
    Scene* scene_ = nullptr;
    std::shared_ptr<Audio> engineSound_;

    double boostTimer_ = 0.0f;
    float originalMaxSpeed_ = 0.0f;
    float originalAcceleration_ = 0.0f;

    void updateBoundingSphere();
    void handleCollisionResponse(Collidable *other);
    void updateBoost(double dt);

    // callback function stored here
    std::function<float(const Vector3& origin,
                        const Vector3& dir,
                        float maxDist)> raycastFunc_;
};

#endif // CAR_HPP
