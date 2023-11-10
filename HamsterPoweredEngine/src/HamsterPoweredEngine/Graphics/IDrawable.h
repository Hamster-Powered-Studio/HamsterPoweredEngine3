#pragma once

#include <glad/gl.h>
#include <cstdint>
#include <glm/mat4x4.hpp>

namespace Hamster
{
    class RenderPass;
    // Implement this interface to make your class drawable
    // Override GetDrawType() to change the draw type
    class IDrawable
    {
    public:
        //virtual void Draw(const glm::mat4& parentTransform = glm::mat4(1.f)) = 0;
        virtual void SubmitToRenderer(RenderPass& renderPass, const glm::mat4& parentTransform = glm::mat4(1.0)) = 0;
        virtual uint32_t GetDrawType() { return GL_TRIANGLES; }
    };
}

