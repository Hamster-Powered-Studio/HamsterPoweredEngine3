#pragma once

#include <glm/fwd.hpp>

#include "IDrawable.h"
#include "ITransformable.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"




namespace Hamster
{
    // Contains vertex data and indices, and a material
    // Can be drawn
    class Mesh : public IDrawable, public ITransformable
    {
    public:
        // Create a mesh from a list of vertices and indices
        Mesh(const std::vector<Vertex>& _vertices, const std::vector<uint32_t>& _indices);
        Mesh(const Mesh& other);
        ~Mesh();

        // Overwrite the vertex data of the mesh
        void SetVertices(const std::vector<Vertex>& _vertices);

        // Overwrite the index data of the mesh
        void SetIndices(const std::vector<uint32_t>& _indices);

        // Set the material of the mesh
        void SetMaterial(std::shared_ptr<Material> _material) { material = _material; }

        // Draw the mesh. Inherited from IDrawable
        //virtual void Draw(const glm::mat4& parentTransform = glm::mat4(1.f)) override;

        // Direct access to the vertex array
        const VertexArray& GetVertexArray() const { return *vertexArray.Get(); }
        const GLHandle<VertexArray> GetVertexArrayHandle() const { return vertexArray; }

        // Direct access to the vertex buffer
        const VertexBuffer& GetVertexBuffer() const { return *vertexBuffer.Get(); }

        // Direct access to the index buffer
        const GLHandle<IndexBuffer>& GetIndexBuffer() const { return indexBuffer; }

        //Get the material assigned to this mesh
        std::shared_ptr<Material> GetMaterial() { return material; }

        // Inherited from IDrawable. Returns GL_TRIANGLES by default
        uint32_t GetDrawType() override { return drawType; }

        // Inherited from IDrawable. Sets the draw type of the mesh
        void SetDrawType(uint32_t _drawType) { drawType = _drawType; }
        void SubmitToRenderer(RenderPass& renderPass, const glm::mat4& parentTransform = glm::mat4(1.0)) override;
        
    protected:
        std::shared_ptr<Material> material;
        GLHandle<VertexArray> vertexArray;
        GLHandle<VertexBuffer> vertexBuffer;
        GLHandle<IndexBuffer> indexBuffer;
        uint32_t drawType = GL_TRIANGLES;
    };
}

