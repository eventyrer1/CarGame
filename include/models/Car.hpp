#ifndef TANK_HPP
#define TANK_HPP

#include <memory>
#include <filesystem>
#include "threepp/threepp.hpp"
#include <keylisteners/car_keylistener.hpp>

using namespace threepp;


class Car : public Object3D {
public:
    explicit Car(std::shared_ptr<Object3D> model);

    static std::shared_ptr<Car> create(const std::filesystem::path &path);

    void update(double deltaTime,
                std::pair<CarKeyListener::CarActionMove, CarKeyListener::CarActionTurn> actions
    );

    std::shared_ptr<Object3D> getModel() const { return model_; }
    //inspirert av sphero.hpp fra threepp eksempel
    PerspectiveCamera &camera();

    // CHANGED: Return Sphere instead of Box3
    Sphere getBoundingSphere() const {
        return boundingSphere_;
    }

    // CHANGED: Collision with Box3 (for trees)
    bool collidesWith(const Box3& otherBox) const {
        return boundingSphere_.intersectsBox(otherBox);
    }

    // ADDED: Collision with other sphere (for future car-to-car)
    bool collidesWith(const Sphere& otherSphere) const {
        return boundingSphere_.intersectsSphere(otherSphere);
    }

    // Add method to enable/update debug visualization
    void setHitboxVisualization(bool enabled, Scene* scene = nullptr);
    void updateHitboxVisualization();

private:
    int speed_ = 10;
    int maxSpeed_ = 100;
    int acceleration_ = 100;
    int rotationSpeed_ = 2;
    float angle_ = 0.0;
    std::shared_ptr<Object3D> model_;
    std::unique_ptr<PerspectiveCamera> camera_;

    // CHANGED: Use Sphere instead of Box3
    Sphere boundingSphere_;

    // For visualization - we'll create a sphere mesh
    std::shared_ptr<Mesh> boundingSphereHelper_;
    Scene* scene_ = nullptr;

    void updateBoundingSphere();
};

#endif // TANK_HPP