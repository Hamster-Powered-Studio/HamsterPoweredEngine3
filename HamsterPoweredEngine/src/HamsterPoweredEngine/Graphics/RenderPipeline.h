#pragma once
#include <queue>
#include <vector>

#include "GLHandle.h"
#include "IDrawable.h"
#include "RenderPass.h"
#include "View.h"


namespace Hamster
{
    class RenderPipeline
    {
    public:
        void Clear();
        
        std::shared_ptr<RenderPass> AddPass(std::shared_ptr<RenderPass> pass)
        {
            return passes.emplace_back(pass);
        }

        const GLHandle<RenderTarget2D> Render();
        GLHandle<RenderTarget2D> GetRenderOutput();
    
    protected:
        std::vector<std::shared_ptr<RenderPass>> passes;
        
    };
}