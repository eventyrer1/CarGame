#include "threepp/threepp.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include "../include/models/Car.hpp"
#include <iostream>

using namespace threepp;

int main() {

    Canvas canvas{Canvas::Parameters().title("Car").size({1280, 720}).antialiasing(8)};
    GLRenderer renderer{canvas.size()};
    renderer.autoClear = false;

    auto scene = Scene::create();
    scene->background = Color::aliceblue;

    auto camera = PerspectiveCamera::create(60, canvas.aspect(), 0.01, 100);
    camera->position.set(-15, 8, 15);

    OrbitControls controls(*camera, canvas);

    auto grid = GridHelper::create(2000, 5000, Color::yellowgreen);
    scene->add(grid);

    auto light1 = DirectionalLight::create(0xffffff, 1.f);
    light1->position.set(1, 1, 1);
    scene->add(light1);

    auto light2 = AmbientLight::create(0xffffff, 1.f);
    scene->add(light2);
    std::shared_ptr<Car> car;
    try {
        std::string carModelPath = std::string(DATA_DIR) + "/models/Car.dae";
        car = Car::create(carModelPath);
        if (car) {
            car->position.set(0, 0, 0);
            scene->add(car);
        } else {
            std::cerr << "Failed to load `Data/Models/Car.dae`\n";
        }
    } catch (const std::exception& ex) {
        std::cerr << "Exception during tank loading: " << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception during tank loading." << std::endl;
    }





    CarKeyListener carKeyListener;
    canvas.addKeyListener(carKeyListener);
    Clock clock;

    canvas.animate([&]() {
        const auto dt = clock.getDelta();
        car->update(dt, carKeyListener.determine_action());
        renderer.clear();
                renderer.render(*scene, *camera);
    });
    return 0;
}