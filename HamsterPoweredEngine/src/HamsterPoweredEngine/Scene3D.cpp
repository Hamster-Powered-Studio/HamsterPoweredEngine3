#include "Scene3D.h"

#include "Application.h"
#include "Components/MeshComponent.h"
#include "Components/RotatorComponent.h"
#include "Components/TransformComponent.h"
#include "Components/ViewComponent.h"
#include "Graphics/ShaderLoader.h"
#include "Systems/MeshRenderSystem.h"
#include "Systems/RotatorSystem.h"
#include "Systems/TransformSystem.h"


using namespace Hamster;

void Scene3D::InitializeDefaultSystems()
{
    BasicTestMat.reset(new Hamster::Material(Hamster::ShaderLoader::Load("Resources/Shaders/BasicLit.glsl")));
    BasicTestMat->SetParameter("uColour", glm::vec4(0, 1, 1, 1));
    
    auto model = CreateEntity();
    auto m = model.AddComponent<MeshComponent>("Resources/Models/Gun.obj");
    auto rotator = model.AddComponent<RotatorComponent>().RotationRate = 15.f;
    model.GetComponent<TransformComponent>().SetScale(2.f);
    model.GetComponent<TransformComponent>().SetRotation({0, 0, 0});
    model.GetComponent<TransformComponent>().SetPosition({0, 0, -1});


    auto model2 = CreateEntity();
    auto m2 = model2.AddComponent<MeshComponent>("Resources/Models/Platform.obj");
    model2.GetComponent<TransformComponent>().SetScale(2.f);
    model2.GetComponent<TransformComponent>().SetRotation({0, 0, 0});
    

    auto light = CreateEntity();
    auto pl = light.AddComponent<PointLightComponent>(PointLightComponent{2.f, 100.f, {1, 0, 0}});
    light.GetComponent<TransformComponent>().SetPosition({0, 1, -2});

    
    auto light2 = CreateEntity();
    auto pl2 = light2.AddComponent<PointLightComponent>(PointLightComponent{10.f, 100.f, {1, 0, 1}});
    light2.GetComponent<TransformComponent>().SetPosition({2, 0, 1});

    auto light3 = CreateEntity();
    auto pl3 = light3.AddComponent<PointLightComponent>(PointLightComponent{7.f, 100.f, {0, 0, 1}});
    light3.GetComponent<TransformComponent>().SetPosition({-2, 0, 0.5f});
    
    m.Model.SetMaterial(BasicTestMat);

    auto cam = CreateEntity("Camera");
    cam.AddComponent<ViewComponent>();
    cam.GetComponent<TransformComponent>().SetPosition({0, 0, -5});

    /*
    // Construct base render pipeline
    std::unique_ptr<RenderPipeline> pipeline = std::make_unique<RenderPipeline>();
    std::shared_ptr<RenderPass> basePass;
    basePass.reset(new RenderPass("BasePass",
        {
                        RenderTarget2D::AttachmentType::COLOR,
                        RenderTarget2D::AttachmentType::DEPTH
                    },
                    {},
        {}));
    View view;
    view.SetPosition({0, 0, -5});
    basePass->SetView(view);
    pipeline->AddPass(basePass);
    
    Application::SetViewportOutput(pipeline->GetRenderOutput());
    */

    EmplaceSystem<RotatorSystem>();
    EmplaceSystem<TransformSystem>();
    EmplaceSystem<MeshRenderSystem>();
    
}

void Scene3D::Update(float ts)
{
    auto registryview = sceneRegistry.view<ViewComponent, TransformComponent>();
    for (auto&[entity, view, transform] : registryview.each())
    {
        view.View.SetPosition(transform.GetPosition());
        //view.View.SetOrientation({0, 0, 1});
    }
    
}

void Scene3D::Begin()
{
    
}
