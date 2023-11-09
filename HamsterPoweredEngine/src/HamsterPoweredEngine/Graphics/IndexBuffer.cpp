#include "IndexBuffer.h"

#include "VertexBuffer.h"

namespace Hamster
{
    
    IndexBuffer::IndexBuffer(const std::vector<uint32_t>& _indices)
    {
        glCreateBuffers(1, &rendererID);
        if (!_indices.empty()) SetData(_indices);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &rendererID);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::SetData(const std::vector<uint32_t>& _indices)
    {
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(uint32_t), _indices.data(), GL_STATIC_DRAW);
        count = (uint32_t)_indices.size();
    }

}

