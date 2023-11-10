#include "RenderPipeline.h"

#include "RenderTarget2D.h"

void Hamster::RenderPipeline::Clear()
{
    for (auto& pass : passes)
    {
        pass->Clear();
    }
}

const GLHandle<Hamster::RenderTarget2D> Hamster::RenderPipeline::Render()
{
    // Render each pass. The output of each pass is the input of the next pass. The final pass is rendered to the screen.
    for (int i = 0; i < passes.size(); i++)
    {
        passes[i]->PrePass();
        passes[i]->Render(glm::mat4(1.0));
        passes[i]->PostPass();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return (*(passes.end()-1))->GetTarget();
}

GLHandle<Hamster::RenderTarget2D> Hamster::RenderPipeline::GetRenderOutput()
{
    return (*(passes.end()-1))->GetTarget();
}
