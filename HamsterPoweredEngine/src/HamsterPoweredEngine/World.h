#pragma once
#include <functional>
#include <slot_map.h>

#include "Node.h"
#include "Node3D.h"
#include "Timestep.h"
#include "Graphics/IDrawable.h"


namespace Hamster
{
    class Layer;
}



class World : public Node3D
{
public:
    friend class EditorLayer;
    friend class GameLayer;
    World();

protected:
    
private:
    //void Draw(const glm::mat4& transform) override;
    void Tick(const Timestep& ts) override;

public:
    void SubmitToRenderer(Hamster::RenderPass& renderPass, const glm::mat4& parentTransform = glm::mat4(1.0)) override;
};
