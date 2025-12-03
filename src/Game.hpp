#pragma once
#include "models/Stone.hpp"
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
#include <optional>
#include <opencv2/core.hpp>
#include <utility>

class Game {
public:
    Game() = default;

    void setup();

    void run();

    struct RenderOutput {
        bool carAvailable{false};
        std::optional<cv::Mat> capturedFrame;
    };

private:
    // Core systems now managed by smart pointers
    std::unique_ptr<threepp::Canvas> canvas_;
    std::unique_ptr<threepp::GLRenderer> renderer_;
    std::shared_ptr<threepp::Scene> scene_;

    std::shared_ptr<Car> car_; // may be null if loading fails
    std::unique_ptr<CollisionManager> collisionManager;

    std::unique_ptr<ObjectSpawner<Tree> > treeSpawner_;
    std::unique_ptr<ObjectSpawner<Human> > humanSpawner_;
    std::unique_ptr<ObjectSpawner<Stone> > stoneSpawner_;
    std::unique_ptr<CarKeyListener> controller_;
    std::unique_ptr<UiManager> ui_;

    std::shared_ptr<threepp::AudioListener> listener_;
    std::unique_ptr<threepp::Audio> victorySound_;
    bool victorySoundPlayed_ = false;
    std::shared_ptr<ScoreManager> score_;
    std::unique_ptr<HUD> hud_;
    std::shared_ptr<Text2D> scoreText_;

    // Fallback camera used if car failed to load
    std::unique_ptr<threepp::PerspectiveCamera> fallbackCamera_;


    // Helpers
    RenderOutput renderFrame(bool captureFrame);
    void sampleAICamera(const RenderOutput &renderOutput, int frameCounter) const;
    void simulateFrame(float dt, const std::pair<CarActions::Move, CarActions::Turn> &actions) const;
};