//
// Created by evest on 04.10.2025.
//inspired by https://github.com/Joranikus/Asteroids/blob/master/include/keylisteners/spaceship_keylistener.hpp

#ifndef CARGAME_CAR_KEYLISTENER_HPP
#define CARGAME_CAR_KEYLISTENER_HPP

#include "threepp/threepp.hpp"


class CarKeyListener : public threepp::KeyListener {
public:
    enum class CarActionMove {
        ACCELERATE,
        DECELERATE,
        NOTHING,
    };

    enum class CarActionTurn {
        TURN_LEFT,
        TURN_RIGHT,
        NOTHING,
    };

    void onKeyPressed(threepp::KeyEvent evt) override;

    void onKeyReleased(threepp::KeyEvent evt) override;


    std::pair<CarActionMove, CarActionTurn> determine_action();

private:
    CarActionTurn turn = CarActionTurn::NOTHING;
    CarActionMove move = CarActionMove::NOTHING;
};

#endif // CARGAME_CAR_KEYLISTENER_HPP
