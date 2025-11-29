//
// Created by evest on 25.10.2025.
//

#ifndef CARGAME_INTERFACECARKEYLISTENER_HPP
#define CARGAME_INTERFACECARKEYLISTENER_HPP

#include <utility>

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

class InterfaceCarKeyListener {
public:

    virtual std::pair<CarActions::Move, CarActions::Turn> getActions() const = 0;
};


#endif //CARGAME_INTERFACECARKEYLISTENER_HPP