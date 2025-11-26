//
// Created by evest on 26.11.2025.
//

#pragma once
#include "threepp/threepp.hpp"
#include <memory>

class Game {

public:
    Game();
    void setup();
    void run();

private:
    threepp::Canvas* canvas;
    threepp::GLRenderer* renderer;
    std::shared_ptr<threepp::Scene> scene;

    // Add all objects you used in main:
    class Car* car;
    class CollisionManager* collisionManager;

    class ObjectSpawner<threepp::Tree>* treeSpawner;
    class ObjectSpawner<threepp::Human>* humanSpawner;

    class CarKeyListener* controller;
    class UiManager* ui;

    threepp::AudioListener* listener;
};
