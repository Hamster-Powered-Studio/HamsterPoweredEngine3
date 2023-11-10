#include "World.h"

#include <iostream>

World::World(): Node3D()
{
}

void World::Tick(const Timestep& ts)
{
    _Tick_Internal(ts);
}

void World::SubmitToRenderer(Hamster::RenderPass& renderPass, const glm::mat4& parentTransform)
{
    Node3D::SubmitToRenderer(renderPass, parentTransform * GetTransform());
}
