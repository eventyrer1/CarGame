#ifndef CAR_VISUAL_HPP
#define CAR_VISUAL_HPP

#include "threepp/threepp.hpp"
#include "CarLogic.hpp"
#include "SpawnableObject.hpp"

class CarVisual : public SpawnableObject {
public:
    explicit CarVisual(std::shared_ptr<threepp::Object3D> model);
    static std::shared_ptr<CarVisual> create(const std::filesystem::path &path);

    void syncWithLogic(const CarLogic &logic);
    threepp::PerspectiveCamera &camera();

private:
    std::unique_ptr<threepp::PerspectiveCamera> camera_;
};

#endif
