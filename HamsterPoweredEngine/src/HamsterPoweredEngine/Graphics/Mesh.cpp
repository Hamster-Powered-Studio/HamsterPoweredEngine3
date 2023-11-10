#include "Mesh.h"

#include <iostream>

#include "RenderObject.h"
#include "RenderPass.h"


namespace Hamster
{
    /*
    void Mesh::Draw(const glm::mat4& parentTransform)
    {
        vertexArray.Get()->Bind();
        if (material) material->Apply();
        glDrawElements(GL_TRIANGLES, indexBuffer.Get()->GetCount(), GL_UNSIGNED_INT, nullptr);
        vertexArray.Get()->Unbind();
    }
    */

    void Mesh::SubmitToRenderer(RenderPass& renderPass, const glm::mat4& parentTransform)
    {
        RenderObject renderobject;
        renderobject.VAO = vertexArray;
        renderobject.Material = material;
        renderobject.Transform = parentTransform * GetTransform();
        renderPass.Submit(renderobject);
    }

    Mesh::Mesh( const std::vector<Vertex>& _vertices, const std::vector<uint32_t>& _indices)
    {
        vertexArray = GraphicsResourceManager::ConstructObject<VertexArray>();
        vertexBuffer = GraphicsResourceManager::ConstructObject<VertexBuffer>(_vertices);
        indexBuffer = GraphicsResourceManager::ConstructObject<IndexBuffer>(_indices);
        vertexArray.Get()->AddVertexBuffer(vertexBuffer);
        vertexArray.Get()->SetIndexBuffer(indexBuffer);
    }

    Mesh::Mesh(const Mesh& other)
        : ITransformable(other)
    {
        vertexArray = other.vertexArray;
        vertexBuffer = other.vertexBuffer;
        indexBuffer = other.indexBuffer;
        material = other.material;
    }

    Mesh::~Mesh()
    {
    }

    void Mesh::SetVertices(const std::vector<Vertex>& _vertices)
    {
        vertexBuffer.Get()->SetData(_vertices);
    }

    void Mesh::SetIndices(const std::vector<uint32_t>& _indices)
    {
        indexBuffer.Get()->SetData(_indices);
    }
    

}
