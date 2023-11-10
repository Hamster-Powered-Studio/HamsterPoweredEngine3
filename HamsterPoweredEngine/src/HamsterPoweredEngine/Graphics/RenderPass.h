#pragma once
#include <queue>
#include <string>

#include "GLHandle.h"

#include "Mesh.h"
#include "RenderTarget2D.h"
#include "WindowPlane.h"
#include "IDrawable.h"
#include "RenderObject.h"

namespace Hamster
{
    class Mesh;
}

namespace Hamster
{
    
    class RenderPass : public IDrawable
    {
    public:
        RenderPass(const std::string& name, std::vector<RenderTarget2D::AttachmentType> attachments, const std::shared_ptr<Material>& material, const std::vector<IDrawable*>& drawables);
        void SetMaterial(const std::shared_ptr<Material>& material) { planeMat = material; }
        const std::shared_ptr<Material>& GetPlaneMaterial() { return planeMat; }
        std::shared_ptr<Material> GetMaterial() {return planeMat;};
        GLHandle<RenderTarget2D> GetTarget() { return target; }
        void SetTarget(GLHandle<RenderTarget2D> _target) { target = _target; }

        void SubmitToRenderer(RenderPass& renderPass, const glm::mat4& parentTransform = glm::mat4(1.0)) override;
        
        
        void Clear();

        void Submit(const RenderObject& object);
        
        // Render all queued objects
        void Render(const glm::mat4& parentTransform);
        void AddObjectToDraw(IDrawable* object);

        void SetView(const View& view);
        const View& GetView() {return view;};
        
        // Draw this render pass to a bound target
        //void Draw(const glm::mat4& parentTransform) override;

        // Draw an item to this render pass
        void DrawObject(RenderObject* item);

        virtual void PrePass() { if (onPrePass) onPrePass(); }
        virtual void PostPass() { if (onPostPass) onPostPass(); }
        void SetOnPrePass(std::function<void()> func) { onPrePass = func; }
        void SetOnPostPass(std::function<void()> func) { onPostPass = func; }
        

    protected:
        std::shared_ptr<Material> planeMat;
        GLHandle<RenderTarget2D> target;
        WindowPlane plane;
        std::string name;

        std::function<void()> onPrePass;
        std::function<void()> onPostPass;

        std::vector<IDrawable*> ObjectsToDraw;
        
        std::queue<RenderObject> RenderQueue;
        View view;
    };
}
