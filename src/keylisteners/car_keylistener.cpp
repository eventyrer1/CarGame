#include "car_keylistener.hpp"

using namespace threepp;


void CarKeyListener::onKeyPressed(KeyEvent evt) {
    if (evt.key == Key::W) {
        move = CarActionMove::ACCELERATE;
    } else if (evt.key == Key::S) {
        move = CarActionMove::DECELERATE;
    }


    if (evt.key == Key::A) {
        turn = CarActionTurn::TURN_LEFT;
    } else if (evt.key == Key::D) {
        turn = CarActionTurn::TURN_RIGHT;
    }
}

void CarKeyListener::onKeyReleased(KeyEvent evt) {
    if (evt.key == Key::W || evt.key == Key::S) {
        move = CarActionMove::NOTHING;
    }
    if (evt.key == Key::A || evt.key == Key::D) {
        turn = CarActionTurn::NOTHING;
    }
}



std::pair<CarKeyListener::CarActionMove, CarKeyListener::CarActionTurn>
CarKeyListener::determine_action() {
    return {move, turn};
}




