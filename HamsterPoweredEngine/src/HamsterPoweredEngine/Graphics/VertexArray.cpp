#include "VertexArray.h"

#include <optional>
#include <glad/gl.h>

#include "GraphicsResourceManager.h"

namespace Hamster
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &rendererID);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &rendererID);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(rendererID);
        if (auto buff = indexBuffer.Get())
        {
            buff->Bind();
        }
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::AddVertexBuffer(const GLHandle<VertexBuffer>& _vertexBuffer)
    {
        Bind();
        _vertexBuffer.Get()->Bind();

        //TODO: Make Dynamic 
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoord));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Colour));


        vertexBuffers.push_back(_vertexBuffer);
    }

    void VertexArray::SetIndexBuffer(const GLHandle<IndexBuffer>& _indexBuffer)
    {
        Bind();
        _indexBuffer.Get()->Bind();

        indexBuffer = _indexBuffer;
    }

    uint32_t VertexArray::GetVertexCount()
    {
        uint32_t count = 0;
        for (auto& vb : vertexBuffers)
        {
            count += vb.Get()->GetCount();
        }
        return count;
    }
}
