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
#include "UiManager.hpp"

#include <opencv2/opencv.hpp>

using namespace threepp;

Game::Game()
    : canvas(nullptr), renderer(nullptr), scene(nullptr),
      car(nullptr), collisionManager(nullptr), treeSpawner(nullptr),
      humanSpawner(nullptr), controller(nullptr), ui(nullptr),
      listener(nullptr) {}

void Game::setup() {

    canvas = new Canvas(Canvas::Parameters()
                            .title("Car")
                            .size({1280, 720})
                            .antialiasing(8));

    renderer = new GLRenderer(canvas->size());
    renderer->autoClear = false;

    scene = Scene::create();

    PerspectiveCamera camera(60, canvas->aspect(), 0.1f, 10000);
    camera.position.set(-15, 8, 15);

    collisionManager = new CollisionManager();

    canvas->onWindowResize([&](const WindowSize& newSize) {
        camera.aspect = newSize.aspect();
        camera.updateProjectionMatrix();
        renderer->setSize(newSize);
    });

    // ---------------- CAR ----------------
    try {
        std::string carModelPath = std::string(DATA_DIR) + "/Models/Car.dae";
        car = Car::create(carModelPath).get();
        car->position.set(0, 0, 0);

        scene->add(car);
        collisionManager->registerCollidable(car);
    } catch (...) {}

    listener = new AudioListener();

    // ---------------- TREE ----------------
    std::string treeModelPath = std::string(DATA_DIR) + "/Models/CartoonTree.obj";
    treeSpawner = new ObjectSpawner<Tree>(scene, treeModelPath, 10);
    treeSpawner->spawnObjects(*collisionManager);

    // ---------------- HUMAN ----------------
    std::string humanModelPath = std::string(DATA_DIR) + "/Models/Human.glb";
    std::string splatSoundPath = std::string(DATA_DIR) + "/Sounds/Splat.wav";

    humanSpawner = new ObjectSpawner<Human>(scene, humanModelPath, 10, listener, splatSoundPath);
    humanSpawner->spawnObjects(*collisionManager);

    // ---------------- CONTROL & UI ----------------
    controller = new CarKeyListener();
    canvas->addKeyListener(*controller);

    ui = new UiManager(static_cast<GLFWwindow*>(canvas->windowPtr()));
    ui->setCar(car);
    ui->setController(controller);
    ui->setHumans(&humanSpawner->getObjects());
}

void Game::run() {

    Clock clock;
    int frameCounter = 0;

    canvas->animate([&]() {
        frameCounter++;

        const auto dt = clock.getDelta();

        renderer->clear();
        renderer->render(*scene, car->camera());

        int fbWidth = canvas->size().width();
        int fbHeight = canvas->size().height();
        if (fbWidth <= 0 || fbHeight <= 0) return;

        std::vector<unsigned char> pixels(fbWidth * fbHeight * 4);

        renderer->readPixels({0, 0}, {fbWidth, fbHeight}, Format::RGBA, pixels.data());

        cv::Mat rgba(fbHeight, fbWidth, CV_8UC4, pixels.data());
        cv::Mat frame;
        cv::cvtColor(rgba, frame, cv::COLOR_RGBA2BGR);
        cv::flip(frame, frame, 0);

        cv::Mat small;
        cv::resize(frame, small, cv::Size(320, 180));

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
