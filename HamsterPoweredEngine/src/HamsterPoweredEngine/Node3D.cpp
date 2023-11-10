#include "Node3D.h"

Node3D::Node3D() : Node()
{
}

void Node3D::SubmitToRenderer(Hamster::RenderPass& renderPass, const glm::mat4& parentTransform)
{
    Node::SubmitToRenderer(renderPass, parentTransform * GetTransform());
}
