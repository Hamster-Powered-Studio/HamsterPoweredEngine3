#pragma once
#include <entt.hpp>

class System
{
public:
    virtual void OnSystemBegin(entt::registry& registry) = 0;
    virtual void OnSystemUpdate(entt::registry& registry, float ts) = 0;
    virtual void OnSystemEnd(entt::registry& registry) = 0;
};
