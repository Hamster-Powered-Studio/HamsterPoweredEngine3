#pragma once
#include <string>
#include <glad/gl.h>
#include <glm/vec2.hpp>


namespace Hamster
{
    class Image;
    
    enum class TextureFormat
    {
        R = GL_RED,
        RG = GL_RG,
        RGB = GL_RGB,
        RGBA = GL_RGBA,
        DEPTH = GL_DEPTH_COMPONENT,
        STENCIL = GL_STENCIL_INDEX,
        DEPTH_STENCIL = GL_DEPTH_STENCIL,
    };

    enum class InternalTextureFormat
    {
        R8 = GL_R8,
        RG8 = GL_RG8,
        RGB8 = GL_RGB8,
        RGBA8 = GL_RGBA8,
        RGBA16F = GL_RGBA16F,
        RGBA32F = GL_RGBA32F,
        R16F = GL_R16F,
        R32F = GL_R32F,
        RG16F = GL_RG16F,
        RG32F = GL_RG32F,
        RGB16F = GL_RGB16F,
        RGB32F = GL_RGB32F,
        DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8,
        DEPTH24 = GL_DEPTH_COMPONENT24,
        STENCIL8 = GL_STENCIL_INDEX8,
    };

    enum class TextureWrap
    {
        REPEAT,
        MIRRORED_REPEAT,
        CLAMP_TO_EDGE,
        CLAMP_TO_BORDER,
    };

    enum class TextureFilter
    {
        NEAREST,
        LINEAR,
    };

    // An OpenGL texture wrapper. Lives on the GPU
    // Can be created from an Image, or a path
    // Can be bound to a slot
    class Texture2D
    {
    public:
        // Create an empty texture with a size and format
        Texture2D(glm::vec2 _size, TextureFormat _format = TextureFormat::RGBA, InternalTextureFormat _internalFormat = InternalTextureFormat::RGBA8);

        // Create a texture from a path
        Texture2D(const std::string& _path, bool _flipVertical = true);

        // Create a texture from an image
        Texture2D(const Image& _image);
        ~Texture2D();

        // Regenerate the texture with a new size. This will delete the old texture data
        void Regenerate(glm::vec2 _size);

        // Bind the texture to a slot
        void Bind(uint32_t slot = 0) const;
        // Unbind the texture from a slot
        void Unbind() const;

        // Set the texture data 
        void SetData(void* _data, glm::vec2 _size);

        // Get the texture width in pixels
        uint32_t GetWidth() const { return width; }
        // Get the texture height in pixels
        uint32_t GetHeight() const { return height; }
        // Get the texture size in pixels
        glm::vec2 GetSize() const { return { width, height }; }

        // Get the OpenGL handle of the texture
        uint32_t GetRendererID() const { return rendererID; }
        // Get the slot the texture is bound to
        uint32_t GetSlot() const { return slot; }

        // Get the texture format
        uint32_t GetFormat() const;
        // Get the texture internal format
        uint32_t GetInternalFormat() const;

        uint32_t GetDataType() const;

        // Set the texture wrap mode
        void SetWrap(TextureWrap _wrap);
        // Get the texture wrap mode
        TextureWrap GetWrap() const { return wrap; }

        // Set the texture filter mode
        void SetFilter(TextureFilter _minFilter, TextureFilter _magFilter);
        // Get the texture min filter mode
        TextureFilter GetMinFilter() const { return minFilter; }
        // Get the texture mag filter mode
        TextureFilter GetMagFilter() const { return magFilter; }
    private:
        int width, height, channels;
        uint32_t rendererID;
        mutable uint32_t slot;
        TextureFormat format;
        InternalTextureFormat internalFormat;
        TextureWrap wrap;
        TextureFilter minFilter;
        TextureFilter magFilter;
    };
}

