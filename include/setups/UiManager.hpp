#pragma once

#include "models/Car.hpp"
#include "models/Human.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "keyListeners/CarKeyListener.hpp"
#include <vector>
#include <memory>
#include "setups/ScoreManager.hpp"

class UiManager {
private:
    CarKeyListener* controller = nullptr;
    ScoreManager* scoreManager = nullptr;
    const std::vector<std::shared_ptr<threepp::Human>>* humans = nullptr;

public:
    Car* car = nullptr;
    bool showDemoWindow = false;

    explicit UiManager(GLFWwindow* window);
    ~UiManager();
    void setScoreManager(ScoreManager* sm) { scoreManager = sm; }
    void setController(CarKeyListener* c) { controller = c; }
    void setCar(Car* carPtr) { car = carPtr; }
    void setHumans(const std::vector<std::shared_ptr<threepp::Human>>* h) { humans = h; }

    void beginFrame();
    void renderUI();
    void endFrame();
};
