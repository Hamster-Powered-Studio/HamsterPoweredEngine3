#include "MeshRenderSystem.h"

#include "HamsterPoweredEngine/Application.h"
#include "HamsterPoweredEngine/Components/LightComponents.h"
#include "HamsterPoweredEngine/Components/MeshComponent.h"
#include "HamsterPoweredEngine/Components/NameComponent.h"
#include "HamsterPoweredEngine/Components/TransformComponent.h"
#include "HamsterPoweredEngine/Components/ViewComponent.h"
#include "HamsterPoweredEngine/Graphics/RenderCommand.h"

void MeshRenderSystem::OnSystemBegin(entt::registry& registry)
{
}

void MeshRenderSystem::OnSystemUpdate(entt::registry& registry, float ts)
{
    
    auto cameras = registry.view<ViewComponent>();
    auto cam = cameras.front();

    BeginScene(registry.get<ViewComponent>(cam).View, Hamster::Application::GetViewportOutput());

    LightData lights;
    
    auto pointLightView = registry.view<PointLightComponent, TransformComponent>();
    lights.PointLights.reserve(pointLightView.size_hint());
    for (auto& [entity, light, transform] : pointLightView.each())
    {
        lights.PointLights.emplace_back(LightData::PointLightData{light, transform.GetPosition()});
    }
    
    auto dirLightView = registry.view<DirectionalLightComponent, TransformComponent>();
    lights.DirLights.reserve(dirLightView.size_hint());
    for (auto& [entity, light, transform] : dirLightView.each())
    {
        lights.DirLights.emplace_back(LightData::DirectionalLightData{light, transform.GetForwardVector()});
    }
    
    auto view = registry.view<MeshComponent, TransformComponent, NameComponent>();
    for (auto& [entity, mesh, transform, name] : view.each())
    {
        for (auto item : mesh.Model.GetMeshes())
        {
            auto obj = item.first;
            Hamster::RenderObject renderobj;
            renderobj.Material = obj.GetMaterial();
            renderobj.Transform = transform.GetTransform();
            renderobj.VAO = obj.GetVertexArrayHandle();
            renderobj.GLDrawMode = Hamster::RenderObject::DrawMode::TRIANGLES;
            DrawObject(&renderobj, lights);
        }
    }
    EndScene();
}

void MeshRenderSystem::OnSystemEnd(entt::registry& registry)
{
}

void MeshRenderSystem::BeginScene(Hamster::View view, GLHandle<Hamster::RenderTarget2D> target)
{
    output = target;
    target.Get()->Bind();
    
    glm::vec2 size = target.Get()->GetSize();
    currentView = view;

    
    RenderCommand::SetViewport(0, 0, size.x, size.y);
    RenderCommand::Clear();
}

void MeshRenderSystem::DrawObject(Hamster::RenderObject* object, std::optional<LightData> lights)
{
    auto mat = object->Material;
    if (mat)
    {
        glm::mat4 vp;
        glm::mat4 vm = currentView.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), output.Get()->GetSize().x / output.Get()->GetSize().y, 0.1f, 1000.f);
        vp = projection * vm;
            
        mat->SetParameter("uModel", object->Transform);
        mat->SetParameter("uView", vm);
        mat->SetParameter("uViewProjection", vp);
        mat->SetParameter("uProjection", projection);
        mat->SetParameter("uResolution", output.Get()->GetSize());
        mat->SetParameter("uTime", Hamster::Application::GetTime());

        if (lights.has_value())
        {
            {
                int count = 0;
                for (auto& light: lights->PointLights)
                {
                    mat->SetParameter("uPointLights[" + std::to_string(count) + "].Intensity", light.Light.Intensity);
                    mat->SetParameter("uPointLights[" + std::to_string(count) + "].Radius", light.Light.Radius);
                    mat->SetParameter("uPointLights[" + std::to_string(count) + "].Colour", light.Light.Colour);
                    mat->SetParameter("uPointLights[" + std::to_string(count) + "].Position", light.Position);
                    count++;
                }
                mat->SetParameter("uPointLightCount", (float)count);
            }
            
            {
                int count = 0;
                for (auto& light: lights->DirLights)
                {
                    mat->SetParameter("uDirectionalLights[" + std::to_string(count) + "].Intensity", light.Light.Intensity);
                    mat->SetParameter("uDirectionalLights[" + std::to_string(count) + "].Colour", light.Light.Colour);
                    mat->SetParameter("uDirectionalLights[" + std::to_string(count) + "].Direction", light.Direction);
                    count++;
                }
                mat->SetParameter("uDirectionalLightCount", (float)count);
            }
            
        }

            
        object->Material->Apply();
    }
    object->Material->Apply();
    object->VAO.Get()->Bind();
    auto vao = object->VAO.Get()->GetVertexCount();
    RenderCommand::DrawElements(object->GLDrawMode, object->VAO.Get()->GetIndexBuffer().Get()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void MeshRenderSystem::EndScene()
{
    currentView = Hamster::View();
}

