#pragma once
#include "models/Stone.hpp""
#include "threepp/threepp.hpp"
#include "setups/ScoreManager.hpp"
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
    Game() = default;

    void setup();

    void run();

private:
    // Core systems now managed by smart pointers
    std::unique_ptr<threepp::Canvas> canvas;
    std::unique_ptr<threepp::GLRenderer> renderer;
    std::shared_ptr<threepp::Scene> scene;

    std::shared_ptr<Car> car; // may be null if loading fails
    std::unique_ptr<CollisionManager> collisionManager;

    std::unique_ptr<ObjectSpawner<Tree> > treeSpawner;
    std::unique_ptr<ObjectSpawner<Human> > humanSpawner;
    std::unique_ptr<ObjectSpawner<Stone> > stoneSpawner;
    std::unique_ptr<CarKeyListener> controller;
    std::unique_ptr<UiManager> ui;

    std::unique_ptr<threepp::AudioListener> listener;
    std::unique_ptr<threepp::Audio> victorySound_;
    bool victorySoundPLayed_ = false;
    ScoreManager score_;
    std::unique_ptr<HUD> hud_;
    std::shared_ptr<Text2D> scoreText_;

    // Fallback camera used if car failed to load
    std::unique_ptr<threepp::PerspectiveCamera> fallbackCamera;


    // Helpers
    void renderFrame();
};
