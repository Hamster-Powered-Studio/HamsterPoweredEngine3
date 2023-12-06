#include "MeshRenderSystem.h"

#include "HamsterPoweredEngine/Application.h"
#include "HamsterPoweredEngine/Components/LightComponents.h"
#include "HamsterPoweredEngine/Components/MeshComponent.h"
#include "HamsterPoweredEngine/Components/NameComponent.h"
#include "HamsterPoweredEngine/Components/TransformComponent.h"
#include "HamsterPoweredEngine/Components/ViewComponent.h"
#include "HamsterPoweredEngine/Graphics/RenderCommand.h"
#include "HamsterPoweredEngine/Graphics/ShaderLoader.h"

void MeshRenderSystem::OnSystemBegin(entt::registry& registry)
{
    gBuffer = GraphicsResourceManager::ConstructObject<Hamster::RenderTarget2D>(Hamster::Application::GetViewportOutput().Get()->GetSize());
    gBuffer.Get()->AddAttachment(Hamster::RenderTarget2D::AttachmentType::COLOR); // Diffuse
    gBuffer.Get()->AddAttachment(Hamster::RenderTarget2D::AttachmentType::COLOR16F); // Normal
    gBuffer.Get()->AddAttachment(Hamster::RenderTarget2D::AttachmentType::COLOR16F); // Position
    gBuffer.Get()->AddAttachment(Hamster::RenderTarget2D::AttachmentType::COLOR16F); // Specular
    gBuffer.Get()->AddAttachment(Hamster::RenderTarget2D::AttachmentType::COLOR16F); // Emissive
    gBuffer.Get()->AddAttachment(Hamster::RenderTarget2D::AttachmentType::DEPTH); // Depth
    gBuffer.Get()->Invalidate();
    lightingPassMaterial = std::make_shared<Hamster::Material>(Hamster::ShaderLoader::Load("Resources/Shaders/LightingPass.glsl"));
}

void MeshRenderSystem::OnSystemUpdate(entt::registry& registry, float ts)
{
    
    auto cameras = registry.view<ViewComponent>();
    auto cam = cameras.front();

    BeginScene(registry.get<ViewComponent>(cam).View, gBuffer);

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
            DrawObject(&renderobj);
        }
    }
    EndScene();

    BeginScene(Hamster::View(), Hamster::Application::GetViewportOutput());

    BindGBufferTextures(lightingPassMaterial.get());
        {
            int count = 0;
            for (auto& light: lights.PointLights)
            {
                lightingPassMaterial->SetParameter("uPointLights[" + std::to_string(count) + "].Intensity", light.Light.Intensity);
                lightingPassMaterial->SetParameter("uPointLights[" + std::to_string(count) + "].Radius", light.Light.Radius);
                lightingPassMaterial->SetParameter("uPointLights[" + std::to_string(count) + "].Colour", light.Light.Colour);
                lightingPassMaterial->SetParameter("uPointLights[" + std::to_string(count) + "].Position", light.Position);
                count++;
            }
            lightingPassMaterial->SetParameter("uPointLightCount", (float)count);
        }
            
        {
            int count = 0;
            for (auto& light: lights.DirLights)
            {
                lightingPassMaterial->SetParameter("uDirectionalLights[" + std::to_string(count) + "].Intensity", light.Light.Intensity);
                lightingPassMaterial->SetParameter("uDirectionalLights[" + std::to_string(count) + "].Colour", light.Light.Colour);
                lightingPassMaterial->SetParameter("uDirectionalLights[" + std::to_string(count) + "].Direction", light.Direction);
                count++;
            }
            lightingPassMaterial->SetParameter("uDirectionalLightCount", (float)count);
        }
    lightingPassMaterial->Apply();
    RenderCommand::DrawScreenPlane();
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

void MeshRenderSystem::DrawObject(Hamster::RenderObject* object)
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

void MeshRenderSystem::BindGBufferTextures(Hamster::Material* material)
{
    auto gBuf = gBuffer.Get();
    material->SetParameter("uGBuffer.Diffuse", gBuf->GetTexture(0));
    material->SetParameter("uGBuffer.Normal", gBuf->GetTexture(1));
    material->SetParameter("uGBuffer.Position", gBuf->GetTexture(2));
    material->SetParameter("uGBuffer.Specular", gBuf->GetTexture(3));
    material->SetParameter("uGBuffer.Emissive", gBuf->GetTexture(4));
    material->SetParameter("uGBuffer.Depth", gBuf->GetTexture(5));
}