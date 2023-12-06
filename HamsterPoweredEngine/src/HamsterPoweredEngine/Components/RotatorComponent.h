#pragma once
#include <glm/vec3.hpp>

struct RotatorComponent
{
    glm::vec3 Axis = {0, 1, 0};
    float RotationRate = 10.f;
};
