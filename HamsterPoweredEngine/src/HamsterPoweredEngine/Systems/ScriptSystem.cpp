#include "ScriptSystem.h"

#include "HamsterPoweredEngine/Components/NativeScriptComponent.h"

void ScriptSystem::OnSystemBegin(entt::registry& registry)
{
}

void ScriptSystem::OnSystemUpdate(entt::registry& registry, float ts)
{
    auto view = registry.view<NativeScriptComponent>();
    for (auto& [entity, script] : view.each())
    {
        script.OnUpdate(1.f/60.f); //TODO pass timestep
    }
    
}

void ScriptSystem::OnSystemEnd(entt::registry& registry)
{
}
