//
// Created by evest on 04.10.2025.
//inspired by https://github.com/Joranikus/Asteroids/blob/master/include/keylisteners/spaceship_keylistener.hpp

#ifndef CARGAME_CAR_KEYLISTENER_HPP
#define CARGAME_CAR_KEYLISTENER_HPP

#include "threepp/threepp.hpp"
#include <set>
#include <map>

class CarKeyListener : public threepp::KeyListener {

public:
    enum class CarAction {
        ACCELERATE,
        DECELERATE,
        TURN_LEFT,
        TURN_RIGHT
    };

    CarKeyListener();

    void onKeyPressed(threepp::KeyEvent evt) override;
    void onKeyReleased(threepp::KeyEvent evt) override;

    bool isKeyPressed(threepp::Key key) const;
    bool isKeyReleased(threepp::Key key) const;

    std::set<CarAction> determine_action();

    void bindKey(threepp::Key key, CarAction action);

private:
    std::set<threepp::Key> keys_pressed;
    std::set<threepp::Key> keys_released;
    std::map<threepp::Key, CarAction> keymap;
};

#endif // CARGAME_CAR_KEYLISTENER_HPP
