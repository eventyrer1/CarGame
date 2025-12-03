//
// Created by evest on 26.11.2025.
//
#include "Game.hpp"

#include "threepp/threepp.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include "setups/ObjectSpawner.hpp"
#include "collision/CollisionManager.hpp"
#include "keyListeners/CarKeyListener.hpp"
#include "setups/UiManager.hpp"
#include "setups/Setup.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <random>
#include <algorithm>


using namespace threepp;





void Game::setup() {
    canvas_ = std::make_unique<Canvas>(Canvas::Parameters()
        .title("Car")
        .size({1280, 720})
        .antialiasing(8));

    renderer_ = std::make_unique<GLRenderer>(canvas_->size());
    renderer_->autoClear = false;

    hud_ = std::make_unique<HUD>(canvas_->size());

    FontLoader fontLoader;
    const auto font = fontLoader.defaultFont();

    TextGeometry::Options textOpts(font, 32, 5); // size=32px, extrude=5
    scoreText_ = Text2D::create(textOpts, "Score: 0");
    scoreText_->setColor(Color::white);

    // Top-right corner overlay
    hud_->add(scoreText_,
              HUD::Options()
              .setNormalizedPosition({0.f, 1.f})
              .setHorizontalAlignment(HUD::HorizontalAlignment::LEFT)
              .setVerticalAlignment(HUD::VerticalAlignment::TOP));


    scene_ = Scene::create();
    setupScene(*scene_);

    // Fallback camera setup (will use car camera if available)
    fallbackCamera_ = std::make_unique<PerspectiveCamera>(60.0f, canvas_->aspect(), 0.1f, 10000.0f);
    fallbackCamera_->position.set(-15, 8, 15);

    collisionManager = std::make_unique<CollisionManager>();
    score_ = std::make_shared<ScoreManager>();

    canvas_->onWindowResize([&](const WindowSize &newSize) {
        if (car_) {
            car_->camera().aspect = newSize.aspect();
            car_->camera().updateProjectionMatrix();
        }
        fallbackCamera_->aspect = newSize.aspect();
        fallbackCamera_->updateProjectionMatrix();
        renderer_->setSize(newSize);
    });

    // ---------------- CAR ----------------
    listener_ = std::make_shared<AudioListener>();

    try {
        std::string carModelPath = std::string(DATA_DIR) + "/Models/Car.dae";
        car_ = Car::create(carModelPath, scene_, listener_, std::string(DATA_DIR) + "/Sounds/CARSOUND.wav");
        if (car_) {
            car_->camera().add(*listener_);
            car_->position.set(0, 0, 0);
            scene_->add(car_);
            collisionManager->registerCollidable(car_);

        } else {
            std::cerr << "Failed to create car from path: " << carModelPath << "\n";
        }
    } catch (const std::exception &ex) {
        std::cerr << "Exception while loading car: " << ex.what() << "\n";
    } catch (...) {
        std::cerr << "Unknown exception while loading car.\n";
    }


    // ---------------- TREE ----------------
    std::string treeModelPath = std::string(DATA_DIR) + "/Models/CartoonTree.obj";
    treeSpawner_ = std::make_unique<ObjectSpawner<Tree> >(
        scene_,
        treeModelPath,
        10,
        -75.0f, 75.0f,
        -75.0f, 75.0f
    );

    treeSpawner_->spawnObjects(*collisionManager);

    // ---------------- STONE ----------------
    std::string stoneModelPath = std::string(DATA_DIR) + "/Models/Stone.glb";
    stoneSpawner_ = std::make_unique<ObjectSpawner<Stone> >(
        scene_,
        stoneModelPath,
        10,
        -50.0f, 50.0f,
        -50.0f, 50.0f
    );

    stoneSpawner_->spawnObjects(*collisionManager);

    // ---------------- HUMAN (Random selection of sound files done by ai) ----------------

    // Build a list of candidate sound files using plain string concatenation
    std::vector<std::string> soundPaths;
    std::string soundsDir = std::string(DATA_DIR) + "/Sounds";


    static const std::vector<std::string> allowedExt = {
        ".wav",
        ".m4a",
        ".mp3",
        ".ogg"
    };

    namespace fs = std::filesystem;

    try {
        if (fs::exists(soundsDir) && fs::is_directory(soundsDir)) {
            for (const auto &entry: fs::directory_iterator(soundsDir)) {
                if (!entry.is_regular_file()) continue;

                // Extract extension
                std::string extLower = entry.path().extension().string();
                std::ranges::transform(extLower, extLower.begin(), ::tolower);

                // Accept a file if the extension matches
                if (std::ranges::find(allowedExt, extLower) != allowedExt.end()) {
                    if (entry.path().filename() != "CARSOUND.wav" && entry.path().filename() != "Victory.wav") {
                        std::string full = entry.path().generic_string();
                        soundPaths.emplace_back(full);
                    }
                }
            }
        }
    } catch (const std::exception &ex) {
        std::cerr << "Error scanning sounds directory: " << ex.what() << "\n";
    }

    // Fallback
    if (soundPaths.empty()) {
        soundPaths.emplace_back(std::string(DATA_DIR) + "/Sounds/Splat.wav");
        std::cerr << "None found >:| !\n";
    }


    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, soundPaths.size() - 1);
    std::string splatSoundPath = soundPaths[dist(rng)];


    std::string humanModelPath = std::string(DATA_DIR) + "/Models/Human.glb";

    humanSpawner_ = std::make_unique<ObjectSpawner<Human> >(
        scene_,
        humanModelPath,
        10,
        -50.0f, 50.0f,
        -50.0f, 50.0f,
        listener_,
        soundPaths,
        score_
    );



    humanSpawner_->spawnObjects(*collisionManager);


    // ---------------- CONTROL & UI ----------------
    controller_ = std::make_unique<CarKeyListener>();
    canvas_->addKeyListener(*controller_);

    ui_ = std::make_unique<UiManager>(static_cast<GLFWwindow *>(canvas_->windowPtr()));
    ui_->setCar(car_.get());
    ui_->setController(controller_.get());
    ui_->setHumans(&humanSpawner_->getObjects());
    ui_->setScoreManager(score_);

    victorySound_               = std::make_unique<Audio>(*listener_, std::string(DATA_DIR) + "/Sounds/Victory.wav");
}

void Game::run() {
    Clock clock;
    int frameCounter = 0;

    canvas_->animate([&]() {
        frameCounter++;

        const auto dt = clock.getDelta();
        const bool captureFrame = controller_ && controller_->getCameraSteeringEnabled() && frameCounter % 10 == 0;
        const auto renderOutput = renderFrame(captureFrame);

        if (!renderOutput.carAvailable) return;

        sampleAICamera(renderOutput, frameCounter);

        const auto actions = controller_ ? controller_->getActions()
                                         : std::pair<CarActions::Move, CarActions::Turn>{
                                               CarActions::Move::NOTHING, CarActions::Turn::NOTHING};
        simulateFrame(dt, actions);
    });
}

Game::RenderOutput Game::renderFrame(bool captureFrame) {
    RenderOutput output{};

    renderer_->clear();
    // Use car camera if car exists, else fallback
    if (car_) {
        renderer_->render(*scene_, car_->camera());
        output.carAvailable = true;
    } else {
        renderer_->render(*scene_, *fallbackCamera_);
    }

    if (captureFrame && output.carAvailable) {
        const int fbWidth = canvas_->size().width();
        const int fbHeight = canvas_->size().height();
        if (fbWidth > 0 && fbHeight > 0) {
            std::vector<unsigned char> pixels(fbWidth * fbHeight * 4);

            renderer_->readPixels({0, 0}, {fbWidth, fbHeight}, Format::RGBA, pixels.data());

            cv::Mat rgba(fbHeight, fbWidth, CV_8UC4, pixels.data());
            cv::Mat frame;
            cv::cvtColor(rgba, frame, cv::COLOR_RGBA2BGR);
            cv::flip(frame, frame, 0);
            output.capturedFrame = frame;
        }
    }

    if (hud_) {

        if (score_->humansHit() < 10) {

            victorySoundPlayed_ = false; //lazy fix for sound playing again if you restart
            scoreText_->setText("Score: " + std::to_string(score_->humansHit()));
            hud_->apply(*renderer_);
        } else {
            if (!victorySoundPlayed_) {
                victorySound_->play();
                victorySoundPlayed_ = true;
            }

            scoreText_->setText("^_^ You win! You monster! ^_^");
            hud_->apply(*renderer_);
        }
    }

    if (ui_) {
        ui_->beginFrame();
        ui_->renderUI();
        ui_->endFrame();
    }

    return output;
}

void Game::sampleAICamera(const RenderOutput &renderOutput, int frameCounter) const {
    if (!renderOutput.carAvailable) return;
    if (!controller_ || !controller_->getCameraSteeringEnabled()) return;
    if (frameCounter % 10 != 0) return;
    if (!renderOutput.capturedFrame.has_value()) return;

    controller_->updateFromCamera(*renderOutput.capturedFrame);
}

void Game::simulateFrame(float dt, const std::pair<CarActions::Move, CarActions::Turn> &actions) const {
    if (!car_) return;

    car_->update(dt, actions.first, actions.second);

    collisionManager->checkCollisions();
    for (auto &stone: stoneSpawner_->getObjects()) {
        stone->update(dt);
    }
}
