#include "RenderPass.h"

#include "HamsterPoweredEngine/Application.h"

namespace Hamster
{
    RenderPass::RenderPass(const std::string& name, std::vector<RenderTarget2D::AttachmentType> attachments, const std::shared_ptr<Material>& _material, const std::vector<IDrawable*>& drawables)
    {
        target = GraphicsResourceManager::ConstructObject<RenderTarget2D>(Application::Get().GetWindowSize());
        for (auto attachment : attachments)
        {
            target.Get()->AddAttachment(attachment);
        }
        planeMat = _material;
        this->name = name;
        this->ObjectsToDraw = drawables;
    }

    void RenderPass::SubmitToRenderer(RenderPass& renderPass, const glm::mat4& parentTransform)
    {
        RenderObject object;
        object.Material = renderPass.GetPlaneMaterial();
        object.Transform = glm::mat4(1);
        object.VAO = plane.GetVertexArrayHandle();
        renderPass.Submit(object);
    }

    void RenderPass::Clear()
    {
        if (target.IsValid())
            target.Get()->Clear();
    }

    void RenderPass::Submit(const RenderObject& object)
    {
        RenderQueue.push(object);
    }

    void RenderPass::Render(const glm::mat4& parentTransform)
    {
        target.Get()->Bind();
        glm::vec2 size = target.Get()->GetSize();
        glViewport(0, 0, size.x, size.y);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        for (auto obj : ObjectsToDraw)
        {
            obj->SubmitToRenderer(*this);
        }
        
        while (!RenderQueue.empty())
        {
            DrawObject(&RenderQueue.front());
            RenderQueue.pop();
        }
    }

    void RenderPass::AddObjectToDraw(IDrawable* object)
    {
        ObjectsToDraw.push_back(object);
    }

    void RenderPass::SetView(const View& view)
    {
        this->view = view;
    }


    void RenderPass::DrawObject(RenderObject* item)
    {
        auto mat = item->Material;
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

}
