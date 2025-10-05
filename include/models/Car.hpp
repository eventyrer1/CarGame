#ifndef TANK_HPP
#define TANK_HPP

#include <memory>
#include <filesystem>
#include "threepp/threepp.hpp"
#include "../keylisteners/car_keylistener.hpp"
using namespace threepp;

//used ai for much of this code
class Car : public Object3D {
public:
    explicit Car(std::shared_ptr<Object3D> model);

    static std::shared_ptr<Car> create(const std::filesystem::path &path);

    void update(double deltaTime,
                std::pair<CarKeyListener::CarActionMove, CarKeyListener::CarActionTurn> actions
    );

    std::shared_ptr<Object3D> getModel() const { return model_; }

private:
    int speed_ = 10;
    int maxSpeed_ = 50;
    int acceleration_ = 400;
    int rotationSpeed_ = 2;
    float angle_ = 0.0;
    std::shared_ptr<Object3D> model_;
};

#endif // TANK_HPP
