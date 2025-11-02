
#ifndef CARGAME_CAR_KEYLISTENER_HPP
#define CARGAME_CAR_KEYLISTENER_HPP

#include "threepp/threepp.hpp"
#include "InterfaceCarKeyListener.hpp"
#include <unordered_set>

class CarKeyListener : public threepp::KeyListener, public InterfaceCarKeyListener {
public:
    void onKeyPressed(threepp::KeyEvent evt) override;
    void onKeyReleased(threepp::KeyEvent evt) override;
    std::pair<CarActions::Move, CarActions::Turn> getActions() const override;

private:
    std::unordered_set<threepp::Key> pressedKeys;
};

#endif // CARGAME_CAR_KEYLISTENER_HPP
