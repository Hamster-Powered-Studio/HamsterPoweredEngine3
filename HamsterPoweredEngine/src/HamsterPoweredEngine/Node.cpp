#include "Node.h"

#include <iostream>

#include "World.h"

Node::Node(std::string_view name)
{
    _name = name;
}

std::string_view Node::GetName()
{
    return _name;
}

const World* Node::GetWorld()
{
    return nullptr;
}

void Node::SetParent(Node* newParent)
{
    if (newParent == Parent) return;
    RemoveFromParent();
    Parent = newParent;
    newParent->AddChild(this);
    
    NullParentOnDestroyCallback = Parent->OnDestroyed.Bind([this]
    {
        Parent = nullptr;
        std::cout << "MY parent died" << std::endl;
    });
    
}

void Node::RemoveFromParent()
{
    if (Parent == nullptr) return;
    for (auto it = Parent->Children.begin(); it != Parent->Children.end(); ++it)
    {
        if (*it == this)
        {
            Parent->Children.erase(it);
            Parent = nullptr;
            Parent->OnDestroyed.Unbind(UnbindOnDestroyOnParentRealloc);
            return;
        }
    }
}

void Node::AddChild(Node* child)
{
    if (child->Parent != this)
    {
        Children.push_back(child);
        child->SetParent(this);
    }
}

void Node::Destroy()
{
    OnDestroy();
}

Node* Node::GetParent()
{
    return Parent;
}


void Node::Init()
{
}

void Node::Tick(const Timestep& ts)
{
}

void Node::OnDestroy()
{
    OnDestroyed.Emit();
}
