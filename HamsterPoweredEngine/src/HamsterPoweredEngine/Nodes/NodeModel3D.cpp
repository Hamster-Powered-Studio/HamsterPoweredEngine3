#include "NodeModel3D.h"

NodeModel3D::NodeModel3D(const std::string& path) : Model(path)
{
}

void NodeModel3D::Init()
{
    Node3D::Init();
}

void NodeModel3D::Tick(const Timestep& ts)
{
    Node3D::Tick(ts);
    Rotate({0, 1, 0}, 100.0 * ts.DeltaSeconds());
}

void NodeModel3D::OnDestroy()
{
    Node3D::OnDestroy();
}

void NodeModel3D::SubmitToRenderer(Hamster::RenderPass& renderPass, const glm::mat4& parentTransform)
{
    Model.SubmitToRenderer(renderPass, parentTransform * GetTransform());
}
