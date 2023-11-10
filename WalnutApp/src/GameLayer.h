#pragma once
#include <memory>

#include "HamsterPoweredEngine/Layer.h"
#include "HamsterPoweredEngine/World.h"
#include "HamsterPoweredEngine/Graphics/RenderPipeline.h"

class GameLayer : public Hamster::Layer
{
public:
    ~GameLayer() override;
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(float ts) override;
    void OnUIRender() override;

    std::shared_ptr<World> world = {};
    std::unique_ptr<Hamster::RenderPipeline> Pipeline;
    GLHandle<Hamster::RenderTarget2D> PipelineRenderOutput;
    std::shared_ptr<Hamster::Material> BasicTestMat;
    Delegate<glm::vec2>::CallbackKey OnViewportResizedCallbackKey;
    
};
