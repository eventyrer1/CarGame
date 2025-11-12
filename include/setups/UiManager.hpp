#pragma once

#include "models/CarLogic.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class UiManager {
public:
    explicit UiManager(GLFWwindow* window);
    ~UiManager();

    void setCarLogic(CarLogic* carLogic);

    void beginFrame();
    void renderUI();
    void endFrame();

private:
    CarLogic* carLogic_ = nullptr;
    bool showDemoWindow = false;
};
