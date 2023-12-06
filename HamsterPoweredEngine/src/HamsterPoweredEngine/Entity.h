#pragma once
#include <cstdint>
#include <entt.hpp>



class Scene;

class Entity
{
public:
    Entity(entt::entity handle, Scene* owningScene) : entityHandle(handle), scene(owningScene) {}
    Entity(const Entity& other) = default;
    
    
    operator entt::entity() const { return entityHandle; }


    template<typename T>
    bool HasComponent()
    {
        return scene->HasComponent<T>(*this);
    }

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
        assert(!HasComponent<T>() && "Entity already has component");
        return scene->AddComponent<T>(*this, std::forward<Args>(args)...);
    }

    template<typename T>
    T& GetComponent()
    {
        assert(HasComponent<T>() && "Entity does not have component");
        return scene->GetComponent<T>(*this);
    }

    template<typename T>
    void RemoveComponent()
    {
        assert(HasComponent<T>() && "Entity does not have component");
        scene->RemoveComponent<T>(*this);
    }
    
private:
    friend class Scene;
    entt::entity entityHandle = entt::null;
    Scene* scene;
};
