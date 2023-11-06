#include "Node.h"

Node::Node(std::string_view name)
{
    _name = name;
}

std::string_view Node::GetName()
{
    return _name;
}
