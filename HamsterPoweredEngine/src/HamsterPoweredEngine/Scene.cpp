#include "Scene.h"

#include "Components/NameComponent.h"
#include "Components/TransformComponent.h"

Entity Scene::CreateEntity(const std::string& name)
{
    Entity entity = {sceneRegistry.create(), this};
    entity.AddComponent<NameComponent>().Name = name;
    entity.AddComponent<TransformComponent>();
    return entity;
}

void Scene::_updateScene(float ts)
{
    for (auto& system : systems)
    {
        if (!system) continue;
        system->OnSystemUpdate(sceneRegistry, ts);
    }

    Update(ts);
}

void Scene::_begin()
{
    for (auto& system : systems)
    {
        if (!system) continue;
        system->OnSystemBegin(sceneRegistry);
    }

    Begin();
}

