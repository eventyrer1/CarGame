#include "models/SpawnableObject.hpp"


using namespace threepp;
// Set a random position and rotation within specified bounds
void SpawnableObject::setRandomPosition(float minX, float maxX, float minZ, float maxZ) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(minX, maxX);
    std::uniform_real_distribution<float> distZ(minZ, maxZ);

    position.set(distX(gen), 0.0f, distZ(gen));

    std::uniform_real_distribution<float> distAngle(0.0f, math::degToRad(360.0f));
    rotation.y = distAngle(gen);

    updateMatrixWorld(true);
    computeBoundingBox();
}
