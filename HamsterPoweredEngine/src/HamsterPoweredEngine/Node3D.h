#pragma once
#include "Node.h"
#include "Graphics/ITransformable.h"

class Node3D : public Node, public Hamster::ITransformable
{
public:
    Node3D();
    void SubmitToRenderer(Hamster::RenderPass& renderPass, const glm::mat4& parentTransform = glm::mat4(1.0)) override;
};
