
#ifndef CARGAME_CAR_KEYLISTENER_HPP
#define CARGAME_CAR_KEYLISTENER_HPP

#include "threepp/threepp.hpp"
#include "InterfaceCarKeylistener.hpp"
#include <unordered_set>

class CarKeyListener : public threepp::KeyListener, public InterfaceCarKeylistener {
public:
    void onKeyPressed(threepp::KeyEvent evt) override;
    void onKeyReleased(threepp::KeyEvent evt) override;
    std::pair<CarActions::Move, CarActions::Turn> getActions() const override;

private:
    std::unordered_set<threepp::Key> pressedKeys;
};

#endif // CARGAME_CAR_KEYLISTENER_HPP
