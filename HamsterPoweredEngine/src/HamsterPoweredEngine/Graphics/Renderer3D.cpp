#include "Renderer3D.h"

#include <glm/ext/matrix_clip_space.hpp>

#include "RenderObject.h"
#include "HamsterPoweredEngine/Application.h"

using namespace Hamster;
/*
void Renderer3D::BeginScene(Hamster::View scene_view)
{
    view = scene_view;
}

void Renderer3D::DrawObject(RenderObject* item)
{
    auto mat = item->Material;
    auto target = Application::GetViewportOutput();
    if (mat)
    {
        glm::mat4 vp;
        glm::mat4 vm = view.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), target.Get()->GetSize().x / target.Get()->GetSize().y, 0.1f, 1000.f);
        vp = projection * vm;
            
        mat->SetParameter("uModel", item->Transform);
        mat->SetParameter("uView", vm);
        mat->SetParameter("uViewProjection", vp);
        mat->SetParameter("uProjection", projection);
        mat->SetParameter("uResolution", target.Get()->GetSize());
        mat->SetParameter("uTime", Application::GetTime());
            
        item->Material->Apply();
    }
        
    item->VAO.Get()->Bind();
    auto vao = item->VAO.Get()->GetVertexCount();
    glDrawElements((unsigned)item->GLDrawMode, item->VAO.Get()->GetIndexBuffer().Get()->GetCount(), GL_UNSIGNED_INT, nullptr);
        
}

void Renderer3D::EndScene()
{
    view = View();
}
*/