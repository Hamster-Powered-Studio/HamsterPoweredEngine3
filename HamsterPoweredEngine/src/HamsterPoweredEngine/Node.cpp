#include "Node.h"

#include <iostream>

#include "World.h"

Node::Node() : _name("Node")
{
    std::cout << "Node ctor" << std::endl;
}

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

void Node::SetParent(const std::shared_ptr<Node>& newParent)
{
    if (newParent.get() == Parent.lock().get()) return;
    RemoveFromParent();
    Parent = newParent;
    newParent->AddChild(shared_from_this());
    
    NullParentOnDestroyCallback = Parent.lock()->OnDestroyed.Bind([this]
    {
        Parent = {};
        std::cout << "MY parent died" << std::endl;
    });
    
}

void Node::RemoveFromParent()
{
    if (auto parentref = Parent.lock())
    {
        for (auto it = parentref->Children.begin(); it != parentref->Children.end(); ++it)
        {
            if (it->get() == this)
            {
                parentref->Children.erase(it);
                parentref = nullptr;
                parentref->OnDestroyed.Unbind(NullParentOnDestroyCallback);
                return;
            }
        }
    }
}

void Node::AddChild(const std::shared_ptr<Node>& child)
{
    if (child->Parent.lock().get() != this)
    {
        Children.push_back(child);
        auto test = this;
        auto shared = shared_from_this();
        child->SetParent(shared);
    }
}

void Node::Destroy()
{
    OnDestroy();
}

std::weak_ptr<Node> Node::GetParent()
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


void Node::_Tick_Internal(const Timestep& ts)
{
    for (auto child : Children)
    {
        if (child)
        {
            child->_Tick_Internal(ts);
            child->Tick(ts);
        }
    }
}

void Node::SubmitToRenderer(Hamster::RenderPass& renderPass, const glm::mat4& parentTransform)
{
    for (auto child : Children)
    {
        child->SubmitToRenderer(renderPass, parentTransform);
    }
}
