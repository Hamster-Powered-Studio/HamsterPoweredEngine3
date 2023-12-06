#pragma once
#include <glm/vec4.hpp>

#include "RenderObject.h"

enum DepthFunc
{
    LESS = GL_LESS,
    MORE = GL_GREATER,
    LEQUAL = GL_LEQUAL
};

enum CullFace
{
    BACK = GL_BACK,
    FRONT = GL_FRONT
};

enum FrontFace
{
    CW = GL_CW,
    CCW = GL_CCW
};

class RenderCommand
{
public:
    static void SetClearColor(glm::vec4 color);
    static void SetViewport(int x, int y, int width, int height);
    static void Clear();
    static void DrawElements(Hamster::RenderObject::DrawMode drawMode, uint32_t indexCount, uint32_t type, const void* indices);
    static void BindDefaultFrameBuffer();
    static void SetDepthTestEnabled(bool enabled);
    static void SetCullFaceEnabled(bool enabled);
    static void SetDepthFunc(DepthFunc func);
    static void SetCullFace(CullFace face);
    static void SetFrontFace(FrontFace face);
};
