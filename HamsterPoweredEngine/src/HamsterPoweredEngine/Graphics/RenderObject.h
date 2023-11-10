#pragma once
#include <glm/fwd.hpp>

#include "GLHandle.h"
#include "Material.h"
#include "VertexArray.h"

namespace Hamster
{
    struct RenderObject
    {
        enum class DrawMode
        {
            TRIANGLES = GL_TRIANGLES,
            TRIANGLE_FAN = GL_TRIANGLE_FAN,
            TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
            QUADS = GL_QUADS,
            LINES = GL_LINES,
            POINTS = GL_POINTS
        };
        
        GLHandle<VertexArray> VAO;
        std::shared_ptr<Material> Material;
        glm::mat4 Transform = glm::mat4(1);
        DrawMode GLDrawMode = DrawMode::TRIANGLES;
    };


}
