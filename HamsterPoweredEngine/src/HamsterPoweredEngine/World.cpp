#include "World.h"

TickManager& World::GetWorldTickManager()
{
    return WorldTickManager;
}

void World::Tick(const Timestep& ts)
{
    WorldTickManager.Tick(ts);
}
