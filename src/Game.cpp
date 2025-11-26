//
// Created by evest on 26.11.2025.
//
#include "Game.hpp"

#include "threepp/threepp.hpp"
#include "threepp/helpers/CameraHelper.hpp"
#include "threepp/loaders/AssimpLoader.hpp"

#include "models/Car.hpp"
#include "models/Tree.hpp"
#include "models/Human.hpp"

#include "setups/ObjectSpawner.hpp"
#include "collision/CollisionManager.hpp"
#include "keyListeners/CarKeyListener.hpp"
#include "setups/UiManager.hpp"
#include "setups/Setup.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace threepp;

Game::Game() = default;

void Game::setup() {

    canvas = std::make_unique<Canvas>(Canvas::Parameters()
                            .title("Car")
                            .size({1280, 720})
                            .antialiasing(8));

    renderer = std::make_unique<GLRenderer>(canvas->size());
    renderer->autoClear = false;

    scene = Scene::create();
    setupScene(*scene);

    // Fallback camera setup (will use car camera if available)
    fallbackCamera = std::make_unique<PerspectiveCamera>(60, canvas->aspect(), 0.1f, 10000);
    fallbackCamera->position.set(-15, 8, 15);

    collisionManager = std::make_unique<CollisionManager>();

    canvas->onWindowResize([&](const WindowSize& newSize) {
        if (car) {
            car->camera().aspect = newSize.aspect();
            car->camera().updateProjectionMatrix();
        }
        fallbackCamera->aspect = newSize.aspect();
        fallbackCamera->updateProjectionMatrix();
        renderer->setSize(newSize);
    });

    // ---------------- CAR ----------------
    try {
        std::string carModelPath = std::string(DATA_DIR) + "/Models/Car.dae";
        car = Car::create(carModelPath);
        if (car) {
            car->position.set(0, 0, 0);
            scene->add(car);
            collisionManager->registerCollidable(car.get());
        } else {
            std::cerr << "Failed to create car from path: " << carModelPath << "\n";
        }
    } catch (const std::exception& ex) {
        std::cerr << "Exception while loading car: " << ex.what() << "\n";
    } catch (...) {
        std::cerr << "Unknown exception while loading car.\n";
    }

    listener = std::make_unique<AudioListener>();
    if (car) { car->camera().add(*listener); }

    // ---------------- TREE ----------------
    std::string treeModelPath = std::string(DATA_DIR) + "/Models/CartoonTree.obj";
    treeSpawner = std::make_unique<ObjectSpawner<Tree>>(scene, treeModelPath, 10);
    treeSpawner->spawnObjects(*collisionManager);

    // ---------------- HUMAN ----------------
    std::string humanModelPath = std::string(DATA_DIR) + "/Models/Human.glb";
    std::string splatSoundPath = std::string(DATA_DIR) + "/Sounds/Splat.wav";
    humanSpawner = std::make_unique<ObjectSpawner<Human>>(scene, humanModelPath, 10, listener.get(), splatSoundPath);
    humanSpawner->spawnObjects(*collisionManager);

    // ---------------- CONTROL & UI ----------------
    controller = std::make_unique<CarKeyListener>();
    canvas->addKeyListener(*controller);

    ui = std::make_unique<UiManager>(static_cast<GLFWwindow*>(canvas->windowPtr()));
    ui->setCar(car.get());
    ui->setController(controller.get());
    ui->setHumans(&humanSpawner->getObjects());
}

void Game::run() {

    Clock clock;
    int frameCounter = 0;

    canvas->animate([&]() {
        frameCounter++;

        const auto dt = clock.getDelta();

        renderer->clear();
        // Use car camera if car exists, else fallback
        if (car) {
            renderer->render(*scene, car->camera());
        } else {
            renderer->render(*scene, *fallbackCamera);
        }

        // If car missing, skip rest to avoid null deref
        if (!car) return;

        int fbWidth = canvas->size().width();
        int fbHeight = canvas->size().height();
        if (fbWidth <= 0 || fbHeight <= 0) return;

        std::vector<unsigned char> pixels(fbWidth * fbHeight * 4);

        renderer->readPixels({0, 0}, {fbWidth, fbHeight}, Format::RGBA, pixels.data());

        cv::Mat rgba(fbHeight, fbWidth, CV_8UC4, pixels.data());
        cv::Mat frame;
        cv::cvtColor(rgba, frame, cv::COLOR_RGBA2BGR);
        cv::flip(frame, frame, 0);

        // Downscale only if needed for performance; we operate on original frame for detection
        if (frameCounter % 10 == 0 && controller->getCameraSteeringEnabled()) {
            controller->updateFromCamera(frame);
        }

        auto [move, turn] = controller->getActions();
        car->update(dt, move, turn);

        collisionManager->checkCollisions();

        ui->beginFrame();
        ui->renderUI();
        ui->endFrame();
    });
}
