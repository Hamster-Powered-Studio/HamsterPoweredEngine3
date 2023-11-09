#pragma once
#include <functional>
#include <slot_map.h>

#include "Node.h"
#include "Node3D.h"
#include "Timestep.h"

class TickManager
{
    friend class World;
public:
    using TickFunction = std::function<void(const Timestep& ts)>;

    void RegisterTickFunction(const TickFunction& function)
    {
        TickFunctions.push_back(function);
    }
    
private:
    std::vector<TickFunction> TickFunctions;
    void Tick(const Timestep& ts)
    {
        for (auto function : TickFunctions)
        {
            function(ts);
        }
    }
};


class World : Node3D
{
public:
    TickManager& GetWorldTickManager();

private:
    
    void Tick(const Timestep& ts) override;
    TickManager WorldTickManager;
};
