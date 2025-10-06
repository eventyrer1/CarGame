#include "threepp/threepp.hpp"
#include "threepp/helpers/CameraHelper.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include "models/Car.hpp"
#include <iostream>
#include "threepp/cameras/PerspectiveCamera.hpp"
#include "setups/setup.hpp"
#include <memory>
using namespace threepp;

int main() {
    Canvas canvas{Canvas::Parameters().title("Car").size({1280, 720}).antialiasing(8)};
    auto size = canvas.size();
    GLRenderer renderer{canvas.size()};
    renderer.autoClear = false;

    auto scene = Scene::create();
    setupScene(*scene);

    PerspectiveCamera camera(60, canvas.aspect(), 0.1f, 1000);
    camera.position.set(-15, 8, 15);
    std::shared_ptr<Car> car = std::make_shared<Car>(nullptr);


    OrbitControls controls(camera, canvas);
    controls.enableKeys = false;
    controls.enableZoom = false;
    controls.enablePan = false;

    canvas.onWindowResize([&](WindowSize newSize) {
        camera.aspect = newSize.aspect();
        camera.updateProjectionMatrix();

        renderer.setSize(newSize);
        size = newSize;
    });


    try {
        std::string carModelPath = std::string(DATA_DIR) + "/models/Car.dae";
        car = Car::create(carModelPath);
        if (car) {
            car->position.set(0, 0, 0);
            scene->add(car);
        } else {
            std::cerr << "Failed to load `Data/Models/Car.dae`\n";
        }
    } catch (const std::exception &ex) {
        std::cerr << "Exception during tank loading: " << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception during tank loading." << std::endl;
    }


    auto &carCamera = car->camera(); // car-attached camera
    auto cameraHelper = CameraHelper::create(carCamera);
    scene->add(cameraHelper);


    CarKeyListener carKeyListener;
    canvas.addKeyListener(carKeyListener);
    Clock clock;

    canvas.animate([&]() {
        const auto dt = clock.getDelta();
        car->update(dt, carKeyListener.determine_action());

        renderer.clear();
        renderer.render(*scene, carCamera);
    });
    return 0;
}
