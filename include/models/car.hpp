#ifndef TANK_HPP
#define TANK_HPP

#include <memory>
#include <filesystem>
#include "threepp/threepp.hpp"
using namespace threepp;
//used ai for much of this code
class car : public Object3D {
public:
    explicit car(std::shared_ptr<Object3D> model);
    static std::shared_ptr<car> create(const std::filesystem::path& path);

    std::shared_ptr<Object3D> getModel() const { return model_; }

public:
    std::shared_ptr<Object3D> model_;
};

#endif // TANK_HPP