#include "threepp/threepp.hpp"
#include "threepp/helpers/CameraHelper.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include "models/Car.hpp"
#include "models/Tree.hpp"
#include "setups/ObjectSpawner.hpp"
#include "collision/CollisionManager.hpp"
#include "keyListeners/CarKeyListener.hpp"
#include "UiManager.hpp"
#include "setups/Setup.hpp"
#include "models/Human.hpp"
#include <iostream>

using namespace threepp;

int main() {
    Canvas canvas{Canvas::Parameters().title("Car").size({1280, 720}).antialiasing(8)};
    GLRenderer renderer{canvas.size()};
    renderer.autoClear = false;

    auto scene = Scene::create();
    setupScene(*scene);

    PerspectiveCamera camera(60, canvas.aspect(), 0.1f, 10000);
    camera.position.set(-15, 8, 15);

    std::shared_ptr<Car> car;

    // CREATE COLLISION MANAGER
    auto collisionManager = std::make_unique<CollisionManager>();

    canvas.onWindowResize([&](const WindowSize &newSize) {
        camera.aspect = newSize.aspect();
        camera.updateProjectionMatrix();
        renderer.setSize(newSize);
    });

    // ---- Car ----
    try {
        std::string carModelPath = std::string(DATA_DIR) + "/Models/Car.dae";
        car = Car::create(carModelPath);
        if (car) {
            car->position.set(0, 0, 0);

            scene->add(car);
            collisionManager->registerCollidable(car.get());
        } else {
            std::cerr << "Failed to load `Data/Models/Car.dae`\n";
        }
    } catch (const std::exception &ex) {
        std::cerr << "Exception during car loading: " << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception during car loading." << std::endl;
    }
    AudioListener listener;
    // ---- Tree ----
    std::string treeModelPath = std::string(DATA_DIR) + "/Models/CartoonTree.obj";
    ObjectSpawner<threepp::Tree> treeSpawner(scene, treeModelPath, 10);
    treeSpawner.spawnObjects(*collisionManager);
    for (auto tree: treeSpawner.getObjects()) {
    }
    // ---- Human ----
    std::string humanModelPath = std::string(DATA_DIR) + "/Models/Human.glb";
    std::string splatSoundPath = std::string(DATA_DIR) + "/Sounds/Splat.wav";

    ObjectSpawner<threepp::Human> humanSpawner(scene, humanModelPath, 10, &listener, splatSoundPath);
    humanSpawner.spawnObjects(*collisionManager);
    for (auto human: humanSpawner.getObjects()) {
    }


    // ---- Camera and input setup ----
    auto &carCamera = car->camera();
    carCamera.add(listener);


    CarKeyListener controller;
    canvas.addKeyListener(controller);

    Clock clock;
    UiManager ui(static_cast<GLFWwindow *>(canvas.windowPtr()));
    ui.setCar(car.get());
    ui.setController(&controller);





    // ---- Main loop ----
    canvas.animate([&]() {
        const auto dt = clock.getDelta();

        // Render FIRST so framebuffer contains the current frame
        renderer.clear();
        renderer.render(*scene, carCamera);
        int fbWidth = canvas.size().width();
        int fbHeight = canvas.size().height();

        std::vector<unsigned char> pixels(fbWidth * fbHeight * 4);

        renderer.readPixels(
            {0, 0},
            {fbWidth, fbHeight},
            Format::RGBA,
            pixels.data()
        );

        cv::Mat rgba(fbHeight, fbWidth, CV_8UC4, pixels.data());
        cv::Mat frame;
        cv::cvtColor(rgba, frame, cv::COLOR_RGBA2BGR);
        cv::flip(frame, frame, 0);
        cv::Mat small;
        //downscales so that my pc doesn't start a fire
        cv::resize(frame, small, cv::Size(320, 180));
        controller.updateFromCamera(frame);

        auto [move, turn] = controller.getActions();
        car->update(dt, move, turn);

        collisionManager->checkCollisions();

        ui.beginFrame();
        ui.renderUI();
        ui.endFrame();
    });


    return 0;
}
