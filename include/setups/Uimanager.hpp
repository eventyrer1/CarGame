#pragma once

#include "Car.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

class UiManager {
public:
    Car* car = nullptr;
    bool showDemoWindow = true;

    explicit UiManager(GLFWwindow* window);
    ~UiManager();

    void setCar(Car* carPtr);
    void beginFrame();
    void renderUI();
    void endFrame();
};
