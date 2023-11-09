#pragma once

#pragma once
#include <cstdint>
#include <memory>



#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "GLHandle.h"

namespace Hamster
{
    // A vertex array object. This is a wrapper around OpenGL's vertex array object. It stores vertex buffers and an index buffer
    // It is used to draw meshes
    class VertexArray
    {
    public:
        // Create a vertex array object
         VertexArray();
        ~VertexArray();

        // Bind the vertex array object
        void Bind() const;
        // Unbind the vertex array object
        void Unbind() const;

        // Add a vertex buffer to the vertex array object
        void AddVertexBuffer(const GLHandle<VertexBuffer>& _vertexBuffer);
        // Set the index buffer of the vertex array object
        void SetIndexBuffer(const GLHandle<IndexBuffer>& _indexBuffer);
        // Get the index buffer of the vertex array object
        const GLHandle<IndexBuffer>& GetIndexBuffer() const { return indexBuffer; }
        // Get the number of vertices in the vertex array object
        uint32_t GetVertexCount();

        operator bool() const
        {
            return rendererID > 0;
        }
    private:
        uint32_t rendererID = 0;
        std::vector<GLHandle<VertexBuffer>> vertexBuffers = {};
        GLHandle<IndexBuffer> indexBuffer;
    };

}
