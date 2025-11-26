#pragma once

#include "threepp/threepp.hpp"

#include "models/Car.hpp"
#include "models/Tree.hpp"
#include "models/Human.hpp"
#include "setups/ObjectSpawner.hpp"
#include "collision/CollisionManager.hpp"
#include "keyListeners/CarKeyListener.hpp"
#include "setups/UiManager.hpp"

#include <memory>

class Game {

public:
    Game();
    void setup();
    void run();

private:
    // Core systems now managed by smart pointers
    std::unique_ptr<threepp::Canvas> canvas;
    std::unique_ptr<threepp::GLRenderer> renderer;
    std::shared_ptr<threepp::Scene> scene;

    std::shared_ptr<Car> car; // may be null if loading fails
    std::unique_ptr<CollisionManager> collisionManager;

    std::unique_ptr<ObjectSpawner<Tree>> treeSpawner;
    std::unique_ptr<ObjectSpawner<Human>> humanSpawner;

    std::unique_ptr<CarKeyListener> controller;
    std::unique_ptr<UiManager> ui;

    std::unique_ptr<threepp::AudioListener> listener;

    // Fallback camera used if car failed to load
    std::unique_ptr<threepp::PerspectiveCamera> fallbackCamera;

    // Helpers
    void renderFrame();
};
