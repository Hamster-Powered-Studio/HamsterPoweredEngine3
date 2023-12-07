#include "GameLayer.h"

#include "HamsterPoweredEngine/Application.h"
#include "HamsterPoweredEngine/Scene3D.h"
#include "HamsterPoweredEngine/Graphics/RenderCommand.h"


using namespace Hamster;

GameLayer::~GameLayer()
{
}      

void GameLayer::OnAttach()
{
    Layer::OnAttach();

    RenderCommand::SetDepthTestEnabled(true);
    RenderCommand::SetDepthFunc(LESS);
           
    RenderCommand::SetCullFaceEnabled(true);
    RenderCommand::SetCullFace(BACK);
    RenderCommand::SetFrontFace(CCW); 
    
    scene = std::make_shared<Scene3D>();
    scene->InitializeDefaultSystems();
    Application::SetVSync(false);
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
    
    scene->_updateScene(ts);
     
    
    // Reset framebuffer to default
    RenderCommand::BindDefaultFrameBuffer();
}
  
void GameLayer::OnUIRender()
{ 
    Layer::OnUIRender();
}        