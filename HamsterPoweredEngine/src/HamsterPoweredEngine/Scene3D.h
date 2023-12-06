#pragma once
#include "Scene.h"

namespace Hamster
{
    class Material;
}

class Scene3D : public Scene
{
public:
    void InitializeDefaultSystems() override;
    void Update(float ts) override;
    void Begin() override;

    std::shared_ptr<Hamster::Material> BasicTestMat;
};
