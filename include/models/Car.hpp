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

    Box3 getBoundingBox() const {
        return boundingBox_;
    }

    bool collidesWith(const Box3& otherBox) const {
        return boundingBox_.intersectsBox(otherBox);
    }

//valgte å definere datamedlemene her i stedenfor å gjør det på Car.cpp siden jeg syns det er mere ryddig
private:
    int speed_ = 10;
    int maxSpeed_ = 100;
    int acceleration_ = 100;
    int rotationSpeed_ = 2;
    float angle_ = 0.0;
    std::shared_ptr<Object3D> model_;
    std::unique_ptr<PerspectiveCamera> camera_;

    Box3 localBoundingBox_;
    Box3 boundingBox_;


    void updateBoundingBox();
};

#endif // TANK_HPP
