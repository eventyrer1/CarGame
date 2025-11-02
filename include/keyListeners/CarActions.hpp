//
// Created by evest on 25.10.2025.
//

#ifndef CARGAME_CARACTIONS_HPP
#define CARGAME_CARACTIONS_HPP

struct CarActions {
    enum class Move {
        ACCELERATE,
        DECELERATE,
        NOTHING,
    };

    enum class Turn {
        TURN_LEFT,
        TURN_RIGHT,
        NOTHING,
    };
};
#endif //CARGAME_CARACTIONS_HPP