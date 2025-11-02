//
// Created by evest on 06.10.2025.
//

#include "Setup.hpp"
#include "threepp/threepp.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
using namespace threepp;
AssimpLoader loader;
void setupScene(Scene &scene) {

    auto light1 = HemisphereLight::create();
    light1->intensity = 0.8f;
    scene.add(light1);

    auto grid = GridHelper::create(100, 50);
    scene.add(grid);
    scene.background = Color::aliceblue;

        auto map = loader.load(std::string(DATA_DIR) + "/models/Track.glb");

        scene.add(map);
        map->scale *= 1;


}