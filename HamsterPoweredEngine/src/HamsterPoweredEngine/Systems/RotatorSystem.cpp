#include "RotatorSystem.h"

#include "HamsterPoweredEngine/Components/RotatorComponent.h"
#include "HamsterPoweredEngine/Components/TransformComponent.h"

void RotatorSystem::OnSystemBegin(entt::registry& registry)
{
}

void RotatorSystem::OnSystemUpdate(entt::registry& registry, float ts)
{
    auto view = registry.view<RotatorComponent, TransformComponent>();
    for (auto& [entity, rotator, transform] : view.each())
    {
        transform.Rotate(rotator.Axis, rotator.RotationRate * ts);
    }
}

void RotatorSystem::OnSystemEnd(entt::registry& registry)
{
}
