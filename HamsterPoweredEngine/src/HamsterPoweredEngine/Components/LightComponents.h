#pragma once
#include <glm/vec3.hpp>

struct PointLightComponent
{
    float Intensity = 1.f;
    float Radius = 100.f;
    glm::vec3 Colour = {1, 1, 1};
};

struct DirectionalLightComponent
{
    float Intensity = 1.f;
    glm::vec3 Colour = {1, 1, 1};
    
};
