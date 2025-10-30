#include "Car.hpp"
#include "CarActions.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Car accelerates up to max speed", "[Car]") {
    auto car = Car::createDummyCar();
    REQUIRE(car != nullptr);

    auto moveAction = CarActions::Move::ACCELERATE;
    auto turnAction = CarActions::Turn::NOTHING;

    for (int i = 0; i < 200; ++i) {
        car->update(0.016, moveAction, turnAction);
    }

    CHECK(car->getSpeed() <= car->getMaxSpeed());
}

TEST_CASE("Car slows down when no input", "[Car]") {
    auto car = Car::createDummyCar();
    REQUIRE(car != nullptr);

    car->setSpeed(20.0f);

    car->update(1.0, CarActions::Move::NOTHING, CarActions::Turn::NOTHING);

    CHECK(car->getSpeed() < 20.0f);
}
