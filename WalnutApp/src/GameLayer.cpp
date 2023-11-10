#include "GameLayer.h"

#include "HamsterPoweredEngine/Application.h"
#include "HamsterPoweredEngine/Graphics/ShaderLoader.h"
#include "HamsterPoweredEngine/Nodes/NodeModel3D.h"

using namespace Hamster;

GameLayer::~GameLayer()
{
}

void GameLayer::OnAttach()
{
    Layer::OnAttach();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    
    world = std::make_shared<World>();

    // Construct base render pipeline
    Pipeline.reset(new RenderPipeline());
    std::shared_ptr<RenderPass> basePass;
    basePass.reset(new RenderPass("BasePass",
        {
                        RenderTarget2D::AttachmentType::COLOR,
                        RenderTarget2D::AttachmentType::DEPTH
                    },
                    {},
        {world.get()}));
    View view;
    view.SetPosition({0, 0, -5});
    basePass->SetView(view);
    Pipeline->AddPass(basePass);

    Application::SetViewportOutput(Pipeline->GetRenderOutput());
    
    BasicTestMat.reset(new Material(ShaderLoader::Load("Resources/Shaders/BasicUnlit.glsl")));
    BasicTestMat->SetParameter("uColour", glm::vec4(0, 1, 1, 1));

    // Spawn 3D Model
    auto model = world->AddChild<NodeModel3D>("Resources/Models/Suzanne.obj").lock();
    model->GetModel().SetMaterial(BasicTestMat);

    // Handle resizing the rendertargets when the imgui viewport gets resized
    OnViewportResizedCallbackKey = Application::OnViewportResized.Bind([basePass](glm::vec2 newSize)
    {
        if (auto target = basePass->GetTarget().Get())
        {
            target->SetSize(newSize);
        }
    });

    
}

void GameLayer::OnDetach()
{
    Layer::OnDetach();
    Application::OnViewportResized.Unbind(OnViewportResizedCallbackKey);
}

void GameLayer::OnUpdate(float ts)
{
    Layer::OnUpdate(ts);
    
    // Update world node and child nodes
    world->Tick(Timestep(ts));

    // Draw world and world objects
    PipelineRenderOutput = Pipeline->Render();

    // Reset framebuffer to default
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GameLayer::OnUIRender()
{
    Layer::OnUIRender();
}
