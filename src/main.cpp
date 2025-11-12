#include "threepp/threepp.hpp"
#include "threepp/helpers/CameraHelper.hpp"
#include "threepp/loaders/AssimpLoader.hpp"

#include "models/CarLogic.hpp"
#include "models/CarVisual.hpp"
#include "models/Tree.hpp"
#include "models/Human.hpp"
#include "setups/ObjectSpawner.hpp"
#include "collision/CollisionManager.hpp"
#include "keyListeners/CarKeyListener.hpp"
#include "UiManager.hpp"
#include "setups/Setup.hpp"

#include <iostream>

using namespace threepp;

int main() {

    // --- Window + renderer ---
    Canvas canvas{Canvas::Parameters().title("Car").size({1280, 720}).antialiasing(8)};
    GLRenderer renderer{canvas.size()};
    renderer.autoClear = false;

    auto scene = Scene::create();
    setupScene(*scene);




    // --- Car logic and visuals ---
    CarLogic carLogic;
    std::shared_ptr<CarVisual> carVisual;

    // --- Collision Manager ---
    auto collisionManager = std::make_unique<CollisionManager>();
    collisionManager->registerCollidable(&carLogic);

    canvas.onWindowResize([&](const WindowSize& newSize) {
        if (carVisual) {
            auto& cam = carVisual->camera();
            cam.aspect = newSize.aspect();
            cam.updateProjectionMatrix();
        }
        renderer.setSize(newSize);
    });

    try {
        std::string carModelPath = std::string(DATA_DIR) + "/Models/Car.dae";
        carVisual = CarVisual::create(carModelPath);
        if (carVisual) {
            scene->add(carVisual);
            carVisual->setHitboxVisualization(true, scene.get());
        } else {
            std::cerr << "Failed to load car model from " << carModelPath << std::endl;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Exception during car loading: " << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception during car loading." << std::endl;
    }

    // --- Audio ---
    AudioListener listener;

    // --- Trees ---
    std::string treeModelPath = std::string(DATA_DIR) + "/Models/CartoonTree.obj";
    ObjectSpawner<threepp::Tree> treeSpawner(scene, treeModelPath, 10);
    treeSpawner.spawnObjects(*collisionManager);
    for (auto& tree : treeSpawner.getObjects()) {
        tree->setHitboxVisualization(true, scene.get());
        tree->updateHitboxVisualization();
    }

    // --- Humans ---
    std::string humanModelPath = std::string(DATA_DIR) + "/Models/Human.glb";
    std::string splatSoundPath = std::string(DATA_DIR) + "/Sounds/Splat.wav";
    ObjectSpawner<threepp::Human> humanSpawner(scene, humanModelPath, 10, &listener, splatSoundPath);
    humanSpawner.spawnObjects(*collisionManager);
    for (auto& human : humanSpawner.getObjects()) {
        human->setHitboxVisualization(true, scene.get());
        human->updateHitboxVisualization();
    }

    // --- Camera setup ---
    auto& carCam = carVisual->camera();
    carCam.add(listener);
    auto cameraHelper = CameraHelper::create(carCam);
    scene->add(cameraHelper);

    // --- Input ---
    CarKeyListener controller;
    canvas.addKeyListener(controller);

    // --- UI ---
    Clock clock;
    UiManager ui(static_cast<GLFWwindow*>(canvas.windowPtr()));
    ui.setCarLogic(&carLogic); // Adjust UiManager to read from CarLogic

    // --- Main loop ---
    canvas.animate([&]() {
        const double dt = clock.getDelta();

        // Get player input
        auto [move, turn] = controller.getActions();

        // Update physics logic only
        carLogic.update(dt, move, turn);

        // Apply logic state to visuals
        carVisual->syncWithLogic(carLogic);

        // Check collisions
        collisionManager->checkCollisions();

        // Render UI
        ui.beginFrame();
        ui.renderUI();

        // Render world
        renderer.clear();
        renderer.render(*scene, carCam);

        ui.endFrame();
    });

    return 0;
}
