#include "TransformSystem.h"

#include "HamsterPoweredEngine/Components/TransformComponent.h"

void TransformSystem::OnSystemBegin(entt::registry& registry)
{
}

void TransformSystem::OnSystemUpdate(entt::registry& registry, float ts)
{
    auto view = registry.view<TransformComponent>();
    for (auto& [entity, transform] : view.each())
    {
        if (transform.IsDirty())
        {
            transform.RecalculateTransform();
        }
    }
}

void TransformSystem::OnSystemEnd(entt::registry& registry)
{
}
