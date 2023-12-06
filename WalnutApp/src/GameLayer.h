#pragma once
#include <memory>

#include "HamsterPoweredEngine/Delegate.h"
#include "HamsterPoweredEngine/Layer.h"
#include "HamsterPoweredEngine/Scene.h"
#include "HamsterPoweredEngine/Graphics/RenderPipeline.h"

class GameLayer : public Hamster::Layer
{
public:
    ~GameLayer() override;
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(float ts) override;
    void OnUIRender() override;
    
    std::shared_ptr<Scene> scene = {};
    
    Delegate<glm::vec2>::CallbackKey OnViewportResizedCallbackKey;
    
};
