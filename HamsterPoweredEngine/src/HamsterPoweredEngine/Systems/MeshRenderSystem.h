﻿#pragma once
#include "HamsterPoweredEngine/System.h"
#include "HamsterPoweredEngine/Components/LightComponents.h"
#include "HamsterPoweredEngine/Components/TransformComponent.h"
#include "HamsterPoweredEngine/Graphics/RenderPipeline.h"

class MeshRenderSystem : public System
{
    struct LightData
    {
        struct PointLightData
        {
            PointLightComponent Light;
            glm::vec3 Position;
        };
        struct DirectionalLightData
        {
            DirectionalLightComponent Light;
            glm::vec3 Direction;
        };
        
        std::vector<PointLightData> PointLights;
        std::vector<DirectionalLightData> DirLights;
    };
    
public:
    void OnSystemBegin(entt::registry& registry) override;
    void OnSystemUpdate(entt::registry& registry, float ts) override;
    void OnSystemEnd(entt::registry& registry) override;

    void BeginScene(Hamster::View view, GLHandle<Hamster::RenderTarget2D> target);
    void DrawObject(Hamster::RenderObject* object, std::optional<LightData> lights);
    void EndScene();
    
    GLHandle<Hamster::RenderTarget2D> output;
    Hamster::View currentView;


};
