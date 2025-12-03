//
// Created by evest on 06.10.2025.

/*
 this was originally done before i hade a game.cpp and game.hpp and everything in there was in main.cpp
 so I wanted to have a separate file for setting up the scene so that main.cpp was cleaner, but now it could be either removed or utilised more,
 but it doesn't impact functionality or readability (in my opinion) so im leaving it as is
*/
#include "Setup.hpp"
#include "threepp/threepp.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
using namespace threepp;
AssimpLoader loader;
void setupScene(Scene &scene) {
    scene.background = Color(0.6f, 0.8f, 1.0f); //makes the skybox blue

    auto light1 = HemisphereLight::create();
    light1->intensity = 0.9f;
    scene.add(light1);


    const auto geometry = PlaneGeometry::create(200, 200, 1, 1);
    const auto material = MeshStandardMaterial::create();
    material->color=Color(0.01f, 1.0f, 0.01f);

    const auto plane = Mesh::create(geometry, material);
    plane->rotation.x = -math::PI / 2; // make it horizontal
    plane->position.y = 0;             // ground level

    scene.add(plane);

}