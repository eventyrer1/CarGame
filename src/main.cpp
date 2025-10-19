#include "threepp/threepp.hpp"
#include "threepp/helpers/CameraHelper.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include "models/Car.hpp"
#include "setups/TreeManager.hpp"
#include "collision/CollisionManager.hpp"
#include <iostream>
#include "threepp/cameras/PerspectiveCamera.hpp"
#include "setups/setup.hpp"
#include <memory>

using namespace threepp;

int main() {
    Canvas canvas{Canvas::Parameters().title("Car").size({1280, 720}).antialiasing(8)};

    GLRenderer renderer{canvas.size()};
    renderer.autoClear = false;

    auto scene = Scene::create();
    setupScene(*scene);

    PerspectiveCamera camera(60, canvas.aspect(), 0.1f, 1000);
    camera.position.set(-15, 8, 15);

    std::shared_ptr<Car> car;
    
    // CREATE COLLISION MANAGER
    auto collisionManager = std::make_unique<CollisionManager>();

    canvas.onWindowResize([&](const WindowSize &newSize) {
        camera.aspect = newSize.aspect();
        camera.updateProjectionMatrix();
        renderer.setSize(newSize);
    });

    // Load the car model
    try {
        std::string carModelPath = std::string(DATA_DIR) + "/models/Car.dae";
        car = Car::create(carModelPath);
        if (car) {
            car->position.set(0, 0, 0);
            car->setHitboxVisualization(true, scene.get());
            scene->add(car);
            
            // REGISTER CAR FOR COLLISION
            collisionManager->registerCollidable(car.get());
        } else {
            std::cerr << "Failed to load `Data/Models/Car.dae`\n";
        }
    } catch (const std::exception &ex) {
        std::cerr << "Exception during car loading: " << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception during car loading." << std::endl;
    }

    std::string treeModelPath = std::string(DATA_DIR) + "/models/Tree.dae";
    auto treeManager = std::make_shared<TreeManager>(scene, treeModelPath, 10);
    treeManager->spawnTrees();
    
    // Enable debug visualization and REGISTER TREES FOR COLLISION
    for (auto& tree : treeManager->getTrees()) {
        tree->setHitboxVisualization(true, scene.get());
        collisionManager->registerCollidable(tree.get());  // ADD THIS
    }

    auto &carCamera = car->camera();
    auto cameraHelper = CameraHelper::create(carCamera);
    scene->add(cameraHelper);

    CarKeyListener carKeyListener;
    canvas.addKeyListener(carKeyListener);
    Clock clock;

    canvas.animate([&]() {
        const auto dt = clock.getDelta();
        car->update(dt, carKeyListener.determine_action());

        // CHECK ALL COLLISIONS WITH ONE LINE!
        collisionManager->checkCollisions();

        renderer.clear();
        renderer.render(*scene, carCamera);
    });
    
    return 0;
}