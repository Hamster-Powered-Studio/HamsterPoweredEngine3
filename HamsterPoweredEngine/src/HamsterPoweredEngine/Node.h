#pragma once
#include <memory>
#include <string>
#include <vector>
#include <glm/fwd.hpp>

#include "Delegate.h"
#include "Timestep.h"
#include "Graphics/IDrawable.h"


class Node;
class World;


class Node: public Hamster::IDrawable, public std::enable_shared_from_this<Node>
{
public:
    friend class World;

    Node();
    explicit Node(std::string_view name);
    
    std::string_view GetName();
    const World* GetWorld();

    void SetParent(const std::shared_ptr<Node>& newParent);
    void RemoveFromParent();
    void AddChild(const std::shared_ptr<Node>& child);
    void Destroy();

    template<typename T, typename ...Args>
    std::weak_ptr<T> AddChild(Args... args)
    {
        std::shared_ptr<T> node;
        node.reset(new T(args...));
        node->Init();
        AddChild(node);
        return(node);
    }
    
    std::weak_ptr<Node> GetParent();
    Delegate<> OnDestroyed;
    
protected:
    virtual void Init();
    virtual void Tick(const Timestep& ts);
    virtual void OnDestroy();
    
    //virtual void Draw(const glm::mat4& transform) override {};

private:
    void _Tick_Internal(const Timestep& ts); // DFS Tick
public:
    void SubmitToRenderer(Hamster::RenderPass& renderPass, const glm::mat4& parentTransform = glm::mat4(1.0)) override;

private:
    std::string _name;
    std::weak_ptr<Node> Parent = {};
    std::vector<std::shared_ptr<Node>> Children;
    
    Delegate<>::CallbackKey NullParentOnDestroyCallback;
    
};
