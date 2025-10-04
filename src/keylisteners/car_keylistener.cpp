#include "car_keylistener.hpp"

using namespace threepp;

CarKeyListener::CarKeyListener() {
    keymap[Key::W] = CarAction::ACCELERATE;
    keymap[Key::S] = CarAction::DECELERATE;
    keymap[Key::A] = CarAction::TURN_LEFT;
    keymap[Key::D] = CarAction::TURN_RIGHT;
}

void CarKeyListener::onKeyPressed(KeyEvent evt) {
    keys_pressed.insert(evt.key);
    keys_released.erase(evt.key);
}

void CarKeyListener::onKeyReleased(KeyEvent evt) {
    keys_pressed.erase(evt.key);
    keys_released.insert(evt.key);
}

bool CarKeyListener::isKeyPressed(Key key) const {
    return keys_pressed.count(key);
}

bool CarKeyListener::isKeyReleased(Key key) const {
    return keys_released.count(key);
}

std::set<CarKeyListener::CarAction> CarKeyListener::determine_action() {
    std::set<CarAction> actions;

    for (auto& [key, action] : keymap) {
        if (isKeyPressed(key)) {
            actions.insert(action);
        }
    }

    return actions;
}

void CarKeyListener::bindKey(Key key, CarAction action) {
    keymap[key] = action;
}
