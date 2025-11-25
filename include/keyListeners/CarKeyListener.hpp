#ifndef CARGAME_CAR_KEYLISTENER_HPP
#define CARGAME_CAR_KEYLISTENER_HPP

#include "threepp/threepp.hpp"
#include "InterfaceCarKeyListener.hpp"
#include <unordered_set>
#include "setups/HumanDetector.hpp"
#include <opencv2/opencv.hpp>

class CarKeyListener : public threepp::KeyListener, public InterfaceCarKeyListener {
public:
    void onKeyPressed(threepp::KeyEvent evt) override;
    void onKeyReleased(threepp::KeyEvent evt) override;

    // Main function the game loop calls
    std::pair<CarActions::Move, CarActions::Turn> getActions() const override;

    void updateFromCamera(const cv::Mat& frame);
    void setCameraSteeringEnabled(bool e) { cameraSteeringEnabled = e; }
    bool getCameraSteeringEnabled() const { return cameraSteeringEnabled; }
private:
    std::unordered_set<threepp::Key> pressedKeys;

    bool cameraSteeringEnabled = false;
    HumanDetector detector;
    float cameraTurnValue = 0.0f; // -1.0 left, +1.0 right
    bool autoAccelerate = false;
};

#endif
