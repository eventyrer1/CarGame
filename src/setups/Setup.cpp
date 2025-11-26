//
// Created by evest on 06.10.2025.
//

#include "Setup.hpp"
#include "threepp/threepp.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
using namespace threepp;
AssimpLoader loader;
void setupScene(Scene &scene) {
    scene.background = Color(0.6f, 0.8f, 1.0f); //makes the skybox blue
    auto light1 = HemisphereLight::create();
    light1->intensity = 0.8f;
    scene.add(light1);
    const auto geometry = PlaneGeometry::create(200, 200, 1, 1);
    const auto material = MeshStandardMaterial::create();
    material->color=Color(0.0f, 1.0f, 0.5f);

    const auto plane = Mesh::create(geometry, material);
    plane->rotation.x = -math::PI / 2; // make it horizontal
    plane->position.y = 0;             // ground level

    scene.add(plane);

    /*auto map = loader.load(std::string(DATA_DIR) + "/models/Track.glb");

    scene.add(map);
    map->scale *= 1;

*/
}