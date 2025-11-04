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

    canvas.onWindowResize([&](const WindowSize& newSize) {
        camera.aspect = newSize.aspect();
        camera.updateProjectionMatrix();
        renderer.setSize(newSize);
    });

    // ---- Car ----
    try {
        std::string carModelPath = std::string(DATA_DIR) + "/models/Car.dae";
        car = Car::create(carModelPath);
        if (car) {
            car->position.set(0, 0, 0);
            car->setHitboxVisualization(true, scene.get());
            scene->add(car);
            collisionManager->registerCollidable(car.get());
        } else {
            std::cerr << "Failed to load `Data/Models/Car.dae`\n";
        }
    } catch (const std::exception& ex) {
        std::cerr << "Exception during car loading: " << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception during car loading." << std::endl;
    }

    // ---- Tree ----
    std::string treeModelPath = std::string(DATA_DIR) + "/models/CartoonTree.obj";
    ObjectSpawner<threepp::Tree> treeSpawner(scene, treeModelPath, 10);
    treeSpawner.spawnObjects(*collisionManager);

    // ---- Tree ----
    std::string humanModelPath = std::string(DATA_DIR) + "/models/Human.glb";
    ObjectSpawner<threepp::Tree> humanSpawner(scene, humanModelPath, 10);
    humanSpawner.spawnObjects(*collisionManager);

    // Hitbox visualization
    for (auto tree : treeSpawner.getObjects()) {
        tree->setHitboxVisualization(true, scene.get());
        tree->updateHitboxVisualization();
    }

    // ---- Camera and input setup ----
    auto& carCamera = car->camera();
    auto cameraHelper = CameraHelper::create(carCamera);
    scene->add(cameraHelper);

    CarKeyListener controller;
    canvas.addKeyListener(controller);

    Clock clock;
    UiManager ui(static_cast<GLFWwindow*>(canvas.windowPtr()));
    ui.setCar(car.get());

    // ---- Main loop ----
    canvas.animate([&]() {
        const auto dt = clock.getDelta();

        auto [move, turn] = controller.getActions();
        car->update(dt, move, turn);

        collisionManager->checkCollisions();

        ui.beginFrame();
        ui.renderUI();

        renderer.clear();
        renderer.render(*scene, carCamera);
        ui.endFrame();
    });

    return 0;
}