#pragma once

#include "Car.hpp"
#include "Human.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "keyListeners/CarKeyListener.hpp"


class UiManager {
private:

    CarKeyListener* controller = nullptr;
    public:
    Car* car = nullptr;
//    Human* humans = nullptr;
    bool showDemoWindow = false;

    explicit UiManager(GLFWwindow* window);
    ~UiManager();
    void setController(CarKeyListener* c) { controller = c; }
    void setCar(Car* carPtr);
   // void setHuman(Human* humanptr);
    void beginFrame();
    void renderUI();
    void endFrame();

};
