//
// Created by evest on 06.10.2025.
//

#include "setup.hpp"
#include "threepp/threepp.hpp"
using namespace threepp;

void setupScene(Scene &scene) {

    auto light1 = HemisphereLight::create();
    light1->intensity = 0.8f;
    scene.add(light1);

    auto grid = GridHelper::create(100, 50);
    scene.add(grid);
    scene.background = Color::aliceblue;

}