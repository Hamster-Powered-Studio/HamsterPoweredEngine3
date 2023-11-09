#pragma once

#include "IDrawable.h"
#include "Material.h"
#include "Texture.h"
#include "View.h"


namespace Hamster
{
    class VertexArray;
    class Shader;

    // A render target is a framebuffer that can be drawn to. It can be used to render to a texture, which can be extracted with GetTexture()
    class RenderTarget2D
    {

    public:
        enum class DrawMode
        {
            FILL,
            WIREFRAME
        };

        enum class AttachmentType
        {
            COLOR = GL_COLOR_ATTACHMENT0,
            COLOR16F = 0,
            DEPTH = GL_DEPTH_ATTACHMENT,
            STENCIL = GL_STENCIL_ATTACHMENT,
            DEPTH_STENCIL = GL_DEPTH_STENCIL_ATTACHMENT,
        };

        struct Attachment
        {
            AttachmentType Type;
            GLHandle<Texture2D> Texture;
        };

        // Create a render target with a given size
        RenderTarget2D(glm::vec2 _size);
        ~RenderTarget2D();

        virtual void Initialize();
        //virtual void SetBufferTextures(Material material);

        // Bind the render target to the current context
        void Bind() const;
        // Unbind the render target from the current context
        void Unbind() const;

        // Regenerate the render target buffers
        void Invalidate();

        // Get the size of the render target in pixels
        glm::vec2 GetSize() const { return size; }
        // Set the size of the render target in pixels
        void SetSize(glm::vec2 _size);

        // Get the texture of the render target
        GLHandle<Texture2D> GetTexture(int index = 0) const { return textures[index].Texture; }
        std::vector<Attachment> GetTextures() const { return textures; }
        int GetTextureCount() const { return (int)textures.size(); }

        // Clear the render target with a given color
        void Clear(const glm::vec4& _color = { 0, 0, 0, 1 });

        // Set the camera view matrix of the render target
        void SetView(const View& _view) { view = _view; }
        // Get the camera view matrix of the render target
        const View& GetView() const { return view; }

        // Draw a vertex array with a given material and transform
        //void Draw(Ref<VertexArray> item, Ref<Material> material, const glm::mat4& transform = glm::mat4(1.f), uint32_t drawType = GL_TRIANGLES);

        // Draw a drawable item with a given transform
        //void Draw(Ref<IDrawable> item, const glm::mat4& parentTransform = glm::mat4(1.f));

        // Set the draw mode of the render target. Can be FILL or WIREFRAME
        void SetDrawMode(DrawMode _drawMode) { drawMode = _drawMode; }
        // Get the draw mode of the render target
        DrawMode GetDrawMode() const { return drawMode; }

        // Adds a new framebuffer texture of the specified type
        GLHandle<Texture2D> AddAttachment(AttachmentType type);

    private:
        uint32_t rendererID = 0; // The OpenGL ID of the render target
        uint32_t depthAttachment = 0; // The depth attachment of the render target
        float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // The color that the render target clears to
        //Ref<Texture2D> texture = nullptr; // The texture that the render target draws to
        glm::vec2 size = { 0.0f, 0.0f }; // The size of the render target in pixels
        View view; // The camera view matrix of the render target
        DrawMode drawMode = DrawMode::FILL; // The draw mode of the render target
        
        std::vector<Attachment> textures = {}; // The attachments of the buffer
    };
}
