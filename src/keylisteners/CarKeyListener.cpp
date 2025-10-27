#include "CarKeyListener.hpp"
using namespace threepp;

void CarKeyListener::onKeyPressed(KeyEvent evt) {
    pressedKeys.insert(evt.key);
}

void CarKeyListener::onKeyReleased(KeyEvent evt) {
    pressedKeys.erase(evt.key);
}

std::pair<CarActions::Move, CarActions::Turn> CarKeyListener::getActions() const {
    using Move = CarActions::Move;
    using Turn = CarActions::Turn;

    Move move = Move::NOTHING;
    Turn turn = Turn::NOTHING;

    if (pressedKeys.contains(Key::W)) move = Move::ACCELERATE;
    else if (pressedKeys.contains(Key::S)) move = Move::DECELERATE;



    if (pressedKeys.contains(Key::A)) turn = Turn::TURN_LEFT;
    else if (pressedKeys.contains(Key::D)) turn = Turn::TURN_RIGHT;

    return {move, turn};
}
