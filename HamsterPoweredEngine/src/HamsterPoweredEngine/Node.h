#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Delegate.h"
#include "Timestep.h"
#include "NodeHandle.h"

class Node;
class World;


class Node
{
public:
    explicit Node(std::string_view name);
    
    std::string_view GetName();
    const World* GetWorld();

    void SetParent(Node* newParent);
    void RemoveFromParent();
    void AddChild(Node* child);
    void Destroy();
    Node* GetParent();
    
    Delegate<> OnDestroyed;
    
protected:
    virtual void Init();
    virtual void Tick(const Timestep& ts);
    virtual void OnDestroy();
    
    std::string _name;
    Node* Parent = nullptr;
    std::vector<Node*> Children;
    
    Delegate<>::CallbackKey NullParentOnDestroyCallback;
    
};
