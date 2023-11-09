#pragma once

#include <vector>

namespace Hamster
{
    class IndexBuffer
    {
    public:
        // Create a new index buffer with the given indices
        IndexBuffer(const std::vector<uint32_t>& _indices);
        ~IndexBuffer();
        
        void Bind() const;
        void Unbind() const;

        // Overwrite the index buffer data with the given indices
        void SetData(const std::vector<uint32_t>& _indices);

        // Get the number of indices in the index buffer
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

