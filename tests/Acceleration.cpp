#include "Car.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Car accelerates up to max speed", "[Car]") {
    auto car = Car::createDummyCar();
    REQUIRE(car != nullptr);

    auto moveAction = CarKeyListener::CarActionMove::ACCELERATE;
    auto turnAction = CarKeyListener::CarActionTurn::NOTHING;

    for (int i = 0; i < 200; ++i)
        car->update(0.016, {moveAction, turnAction});

    CHECK(car->getSpeed() <= car->getMaxSpeed());
}

TEST_CASE("Car slows down when no input", "[Car]") {
    auto car = Car::createDummyCar();
    REQUIRE(car != nullptr);

    car->setSpeed(20.0);

    car->update(1.0, {CarKeyListener::CarActionMove::NOTHING,
                       CarKeyListener::CarActionTurn::NOTHING});

    CHECK(car->getSpeed() < 20.0);
}
