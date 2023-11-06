#pragma once
#include <string>

class Node
{
public:
    explicit Node(std::string_view name);

    std::string_view GetName();
protected:
    std::string _name;
    
};
