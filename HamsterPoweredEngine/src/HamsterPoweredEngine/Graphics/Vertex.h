#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Hamster
{
    // A vertex with position, normal, texture coordinate, colour and texture index data
    struct Vertex
    {
        glm::vec3 Position = {0, 0, 0};
        glm::vec3 Normal = {0, 1, 0};
        glm::vec2 TexCoord = {0, 0};
        glm::vec4 Colour = {1, 1, 1, 1};
    };

}
