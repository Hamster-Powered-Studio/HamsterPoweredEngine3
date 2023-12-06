#pragma once
#include "HamsterPoweredEngine/System.h"

class ScriptSystem : public System
{
public:
    void OnSystemBegin(entt::registry& registry) override;
    void OnSystemUpdate(entt::registry& registry, float ts) override;
    void OnSystemEnd(entt::registry& registry) override;
};
