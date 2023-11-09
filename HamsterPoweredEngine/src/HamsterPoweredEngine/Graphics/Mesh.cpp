#include "Mesh.h"

#include <iostream>


namespace Hamster
{
    //void Mesh::OnDraw(RenderTarget2D& _target, const glm::mat4& parentTransform)
    //{
        //_target.Draw(vertexArray, material, parentTransform * GetTransform(), drawType);
    //}

    Mesh::Mesh( const std::vector<Vertex>& _vertices, const std::vector<uint32_t>& _indices)
    {
        //vertexArray = VertexArray();
        //vertexBuffer = VertexBuffer(_vertices);
        //indexBuffer = IndexBuffer(_indices);
        //vertexArray.AddVertexBuffer(&vertexBuffer);
        //vertexArray.SetIndexBuffer(indexBuffer);
    }

    Mesh::~Mesh()
    {
        
    }

    void Mesh::SetVertices(const std::vector<Vertex>& _vertices)
    {
        vertexBuffer->SetData(_vertices);
    }

    void Mesh::SetIndices(const std::vector<uint32_t>& _indices)
    {
        indexBuffer->SetData(_indices);
    }
    

}
