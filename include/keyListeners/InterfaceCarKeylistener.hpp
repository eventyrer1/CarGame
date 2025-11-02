//
// Created by evest on 25.10.2025.
//

#ifndef CARGAME_INTERFACECARKEYLISTENER_HPP
#define CARGAME_INTERFACECARKEYLISTENER_HPP
#include "CarActions.hpp"
#include <utility>



class InterfaceCarKeylistener {
public:

    virtual std::pair<CarActions::Move, CarActions::Turn> getActions() const = 0;
};


#endif //CARGAME_INTERFACECARKEYLISTENER_HPP