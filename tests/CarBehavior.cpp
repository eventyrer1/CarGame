#include "Car.hpp"
#include <catch2/catch_test_macros.hpp>
#include <cmath>
//there is probably a library that does this, but I couldn't find it.
constexpr float EPS = 0.01f;
inline bool approxEqual(float a, float b, float eps = EPS) {
    return std::fabs(a - b) < eps;
}

TEST_CASE ("Speed boost increases max speed and acceleration temporarily", "[Car][Boost]") {
    auto car = Car::createDummyCar();
    REQUIRE(car != nullptr);

    float baseMax = car->getMaxSpeed();
    float baseAcc = car->getAcceleration();

    car->applyRotationChanger(50.f, 1.0);
    CHECK(approxEqual(car->getMaxSpeed(), baseMax + 50.f));
    CHECK(approxEqual(car->getAcceleration(), baseAcc + 10.f)); // 0.2 * 50

    // advance time less than duration
    car->update(0.5, CarActions::Move::NOTHING, CarActions::Turn::NOTHING);
    CHECK(approxEqual(car->getMaxSpeed(), baseMax + 50.f));

    // advance past duration to revert
    car->update(0.6, CarActions::Move::NOTHING, CarActions::Turn::NOTHING);
    CHECK(approxEqual(car->getMaxSpeed(), baseMax));
    CHECK(approxEqual(car->getAcceleration(), baseAcc));
}

TEST_CASE("Turning left/right adjusts angle and affects movement direction", "[Car][Turn]") {
    auto car = Car::createDummyCar();
    REQUIRE(car != nullptr);

    car->update(0.5, CarActions::Move::ACCELERATE, CarActions::Turn::NOTHING);
    auto posBeforeTurn = car->position;

    // turn left while moving
    car->update(0.5, CarActions::Move::ACCELERATE, CarActions::Turn::TURN_LEFT);
    auto posAfterLeft = car->position;

    CHECK(!approxEqual(posAfterLeft.x, posBeforeTurn.x));
    CHECK(!approxEqual(posAfterLeft.z, posBeforeTurn.z));

    // turn right while moving
    car->update(0.5, CarActions::Move::ACCELERATE, CarActions::Turn::TURN_RIGHT);
    auto posAfterRight = car->position;

    bool changedX = !approxEqual(posAfterRight.x, posAfterLeft.x);
    bool changedZ = !approxEqual(posAfterRight.z, posAfterLeft.z);
    bool moved = changedX || changedZ;

    CHECK(moved);

}

TEST_CASE("Drag reduces speed when no input", "[Car][Drag]") {
    auto car = Car::createDummyCar();
    REQUIRE(car != nullptr);

    car->setSpeed(40.0f);
    car->update(1.0, CarActions::Move::NOTHING, CarActions::Turn::NOTHING);
    CHECK(car->getSpeed() < 40.0f);

    car->setSpeed(0.05f);
    car->update(1.0, CarActions::Move::NOTHING, CarActions::Turn::NOTHING);
    CHECK(approxEqual(car->getSpeed(), 0.0f));
}

TEST_CASE("Reset clears movement and boost state", "[Car][Reset]") {
    auto car = Car::createDummyCar();
    REQUIRE(car != nullptr);

    car->setSpeed(100.0f);
    car->applyRotationChanger(80.f, 2.0);
    car->update(0.5, CarActions::Move::ACCELERATE, CarActions::Turn::TURN_LEFT);

    car->reset();
    CHECK(approxEqual(car->getSpeed(), 0.0f));

    float baseMax = car->getMaxSpeed();
    float baseAcc = car->getAcceleration();

    car->applyRotationChanger(20.f, 0.5);
    CHECK(approxEqual(car->getMaxSpeed(), baseMax + 20.f));
    CHECK(approxEqual(car->getAcceleration(), baseAcc + 4.f));
}
