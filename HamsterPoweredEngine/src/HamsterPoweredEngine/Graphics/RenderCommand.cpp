#include "RenderCommand.h"

#include "Plane.h"
#include "glad/gl.h"

void RenderCommand::SetClearColor(glm::vec4 color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void RenderCommand::SetViewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

void RenderCommand::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderCommand::DrawElements(Hamster::RenderObject::DrawMode drawMode, uint32_t indexCount, uint32_t type,
    const void* indices)
{
    glDrawElements(static_cast<GLenum>(drawMode), static_cast<int>(indexCount), type, indices);
}

void RenderCommand::BindDefaultFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderCommand::SetDepthTestEnabled(bool enabled)
{
    if (enabled) glEnable(GL_DEPTH_TEST);
    else glDisable(GL_DEPTH_TEST);
}

void RenderCommand::SetCullFaceEnabled(bool enabled)
{
    if (enabled) glEnable(GL_CULL_FACE);
    else glDisable(GL_CULL_FACE);
}

void RenderCommand::SetDepthFunc(DepthFunc func)
{
    glDepthFunc(func);
}

void RenderCommand::SetCullFace(CullFace face)
{
    glCullFace(face);
}

void RenderCommand::SetFrontFace(FrontFace face)
{
    glFrontFace(face);
}

void RenderCommand::DrawScreenPlane()
{
    if (!ScreenPlane) ScreenPlane.reset(new Hamster::Plane());
    ScreenPlane->GetVertexArray().Bind();
    ScreenPlane->GetVertexArray().GetIndexBuffer().Get()->Bind();

    DrawElements(Hamster::RenderObject::DrawMode::TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
