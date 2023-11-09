#pragma once

#include <glad/gl.h>
#include <cstdint>
#include <vector>

#include "Vertex.h"

namespace Hamster
{
    // A vertex buffer object. This is a wrapper around OpenGL's vertex buffer object. It stores vertex data
    class VertexBuffer
    {
    public:
        enum class Usage
        {
            Static = GL_STATIC_DRAW,
            Dynamic = GL_DYNAMIC_DRAW,
            Stream = GL_STREAM_DRAW
        };
        
        // Create a vertex buffer object with a vector of vertices
        VertexBuffer(const std::vector<Vertex>& _vertices, Usage _usage = Usage::Static);
        ~VertexBuffer();

        // Bind the vertex buffer object
        void Bind() const;
        // Unbind the vertex buffer object
        void Unbind() const;

        // Set the data of the vertex buffer object with a vector of vertices
        void SetData(const std::vector<Vertex>& _vertices, Usage _usage = Usage::Static);

        // Get the number of vertices in the vertex buffer object
        uint32_t GetCount() const { return count; }

        operator bool() const
        {
            return rendererID > 0;
        }
    private:
        uint32_t rendererID = 0;
        uint32_t count = 0;
    };
}
