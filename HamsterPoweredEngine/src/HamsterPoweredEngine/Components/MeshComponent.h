#pragma once
#include "HamsterPoweredEngine/Graphics/Mesh.h"
#include "HamsterPoweredEngine/Graphics/Model.h"

struct MeshComponent
{
    MeshComponent(const std::string& path = "Resources/Models/Gun.obj") : Model(path) {}
    Hamster::Model Model;
};
