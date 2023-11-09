#include "VertexBuffer.h"

namespace Hamster
{

    VertexBuffer::VertexBuffer(const std::vector<Hamster::Vertex>& _vertices = {}, Usage _usage)
    {
        glGenBuffers(1, &rendererID);
        if (!_vertices.empty())
        {
            SetData(_vertices);
        }
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &rendererID);
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::SetData(const std::vector<Hamster::Vertex>& _vertices, Usage _usage)
    {
        Bind();
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Hamster::Vertex), _vertices.data(), static_cast<GLenum>(_usage));
        count = (uint32_t)_vertices.size();
    }
}

