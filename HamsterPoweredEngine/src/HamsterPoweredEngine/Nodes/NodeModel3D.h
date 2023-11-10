#pragma once
#include "HamsterPoweredEngine/Node3D.h"
#include "HamsterPoweredEngine/Graphics/Model.h"

class NodeModel3D : public Node3D
{
public:
    NodeModel3D(const std::string& path);
    
    void Init() override;
    void Tick(const Timestep& ts) override;
    void OnDestroy() override;
    //void Draw(const glm::mat4& transform) override;
    
    Hamster::Model& GetModel() { return Model; }
    void SubmitToRenderer(Hamster::RenderPass& renderPass, const glm::mat4& parentTransform = glm::mat4(1.0)) override;

protected:
    Hamster::Model Model = Hamster::Model("Resources/Models/Suzanne.obj");
};
