#include "threepp/threepp.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include "../include/models/Tank.hpp"
#include <iostream>

using namespace threepp;

namespace {
    auto createWireframe(const BufferGeometry& geometry) {

        const auto material = LineBasicMaterial::create({{"color", Color::black}});
        return LineSegments::create(WireframeGeometry::create(geometry), material);
    }

    void updateGroupGeometry(Mesh& mesh, const PlaneGeometry::Params& params) {

        const auto geometry = PlaneGeometry::create(params);
        mesh.setGeometry(geometry);

        mesh.children[0]->removeFromParent();
        mesh.add(createWireframe(*geometry));
    }

    auto createMesh(const PlaneGeometry::Params& params) {

        const auto geometry = PlaneGeometry::create(params);
        const auto material = MeshBasicMaterial::create();
        material->side = Side::Double;

        auto mesh = Mesh::create(geometry, material);
        mesh->add(createWireframe(*geometry));

        return mesh;
    }
}

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
        auto tank = Tank::create(std::filesystem::path("Data/Models/Car.dae"));
        if (tank) {
            tank->position.set(0, 5, 0);
            scene->add(tank);
        } else {
            std::cerr << "Failed to load `Data/Models/Car.dae`\n";
        }
    } catch (const std::exception& ex) {
        std::cerr << "Exception during tank loading: " << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception during tank loading." << std::endl;
    }

        PlaneGeometry::Params params{1000,1000};

        const auto mesh = createMesh(params);
        scene->add(mesh);
        mesh->rotateX(90);
    Clock clock;
    canvas.animate([&]() {
        const auto dt = clock.getDelta();
        renderer.clear();
                renderer.render(*scene, *camera);
    });
    return 0;
}