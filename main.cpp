#include "threepp/threepp.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include "Tank.hpp"
#include <iostream>

using namespace threepp;


int main() {
    Canvas canvas{Canvas::Parameters().title("Tank").size({1280, 720}).antialiasing(8)};
    GLRenderer renderer{canvas.size()};
    renderer.autoClear = false;

    auto scene = Scene::create();
    scene->background = Color::aliceblue;

    auto camera = PerspectiveCamera::create(60, canvas.aspect(), 0.01, 100);
    camera->position.set(-15, 8, 15);

    OrbitControls controls(*camera, canvas);

    auto grid = GridHelper::create(20, 10, Color::yellowgreen);
    scene->add(grid);

    auto light1 = DirectionalLight::create(0xffffff, 1.f);
    light1->position.set(1, 1, 1);
    scene->add(light1);

    auto light2 = AmbientLight::create(0xffffff, 1.f);
    scene->add(light2);
    try {
        auto tank = Tank::create(std::filesystem::path("Data/Models/m26.dae"));
        if (tank) {
            tank->position.set(0, 0, 0);
            scene->add(tank);
        } else {
            std::cerr << "Failed to load `Data/Models/m26.dae`\n";
        }
    } catch (const std::exception& ex) {
        std::cerr << "Exception during tank loading: " << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception during tank loading." << std::endl;
    }

    Clock clock;
    canvas.animate([&]() {
        const auto dt = clock.getDelta();
        renderer.clear();
                renderer.render(*scene, *camera);
    });
    return 0;
}