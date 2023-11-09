#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>

namespace Hamster
{
    // Implement this interface to make your class drawable
    // Override GetDrawType() to change the draw type
    class IDrawable
    {
    public:
        //virtual void OnDraw(RenderTarget2D& _target, const glm::mat4& parentTransform = glm::mat4(1.f)) = 0;
        virtual uint32_t GetDrawType() { return GL_TRIANGLES; }
    };
}

