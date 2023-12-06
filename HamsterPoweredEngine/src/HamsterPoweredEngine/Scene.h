#pragma once
#include <iostream>

#include "Entity.h"
#include "entt.hpp"
#include "System.h"

class Scene
{
public:
    Entity CreateEntity(const std::string& name = "Entity");

    template<typename T, typename... Args>
    T& AddComponent(const Entity& entity, Args&&... args);

    template<typename T>
    void RemoveComponent(const Entity& entity);

    template<typename T>
    bool HasComponent(const Entity& entity);

    template<typename T>
    T& GetComponent(const Entity& entity);

    template<typename T>
    void AddSystem(std::unique_ptr<T> system);

    template<typename T, typename...Args>
    void EmplaceSystem(Args&&... args);
    
    virtual void InitializeDefaultSystems() = 0;
    virtual void Begin() = 0;
    virtual void Update(float ts) = 0;


private:
    void _updateScene(float ts);
    void _begin();

protected:
    entt::registry sceneRegistry;
    std::vector<std::unique_ptr<System>> systems;

    friend class GameLayer;
};

template <typename T, typename... Args>
T& Scene::AddComponent(const Entity& entity, Args&&... args)
{
    return sceneRegistry.emplace<T>(entity, std::forward<Args>(args)...);
}

template <typename T>
void Scene::RemoveComponent(const Entity& entity)
{
    sceneRegistry.remove<T>(entity);
}

template <typename T>
bool Scene::HasComponent(const Entity& entity)
{
    return sceneRegistry.any_of<T>(entity);
}

template <typename T>
T& Scene::GetComponent(const Entity& entity)
{
    return sceneRegistry.get<T>(entity);
}

template <typename T>
void Scene::AddSystem(std::unique_ptr<T> system)
{
    system->OnSystemBegin(sceneRegistry);
    systems.push_back(std::move(system));
}

template <typename T, typename...Args>
void Scene::EmplaceSystem(Args&&... args)
{
    std::unique_ptr<T> system = std::make_unique<T>(std::forward<Args>(args)...);
    AddSystem(std::move(system));
}

