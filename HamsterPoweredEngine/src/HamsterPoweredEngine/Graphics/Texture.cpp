#include "Texture.h"

#include "Texture.h"

#include <iostream>
#include <ostream>
#include <stb_image.h>
#include <glad/gl.h>
#include "Image.h"
#include <glm/glm.hpp>

#include "HamsterPoweredEngine/Application.h"
#include "HamsterPoweredEngine/Application.h"


#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif


namespace Hamster
{
    Texture2D::Texture2D(glm::vec2 _size, TextureFormat _format, InternalTextureFormat _internalFormat)
    {
        // Generate the texture
        glGenTextures(1, &rendererID);
        Bind();

        internalFormat = _internalFormat;
        format = _format;
        width = (int)_size.x;
        height = (int)_size.y;
    
    
        // Create an empty texture with the given size
        glTexImage2D( GL_TEXTURE_2D, 0, (int)internalFormat, (uint32_t)_size.x, (uint32_t)_size.y, 0, (int)format, GetDataType(), nullptr );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    }

    Texture2D::Texture2D(const std::string& _path, bool _flipVertical)
    {
        stbi_set_flip_vertically_on_load(_flipVertical);
        stbi_uc* data = stbi_load(_path.c_str(), &width, &height, &channels, 0);
        if (data)
        {
            glGenTextures(1, &rendererID);
            Bind();

            // Get the image format
            format = TextureFormat::RGBA;
            internalFormat = InternalTextureFormat::RGBA8;
            if (channels == 3)
            {
                format = TextureFormat::RGB;
                internalFormat = InternalTextureFormat::RGB8;
            }
            
            else if (channels == 2)
            {
                format = TextureFormat::RG;
                internalFormat = InternalTextureFormat::RG8;
            }
            
            else if (channels == 1)
            {
                format = TextureFormat::R;
                internalFormat = InternalTextureFormat::R8;
            }
            
            // Create the texture
            glTexImage2D( GL_TEXTURE_2D, 0, GetInternalFormat(), width, height, 0, GetFormat(), GetDataType(), data );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load texture: " << _path << std::endl;
        }
    }

    Texture2D::Texture2D(const Image& _image)
    {
        glGenTextures(1, &rendererID);
        Bind();

        // Get the image format
        format = TextureFormat::RGBA;
        internalFormat = InternalTextureFormat::RGBA8;
        if (_image.GetChannels() == 3)
        {
            format = TextureFormat::RGB;
            internalFormat = InternalTextureFormat::RGB8;
        }
        
        else if (_image.GetChannels() == 2)
        {
            format = TextureFormat::RG;
            internalFormat = InternalTextureFormat::RG8;
        }
        
        else if (_image.GetChannels() == 1)
        {
            format = TextureFormat::R;
            internalFormat = InternalTextureFormat::R8;
        }
        
        // Create the texture
        glTexImage2D( GL_TEXTURE_2D, 0, (int)GetInternalFormat(), (int)_image.GetWidth(), (int)_image.GetHeight(), 0, GetFormat(), GetDataType(), _image.GetData().data() );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &rendererID);
    }

    void Texture2D::Regenerate(glm::vec2 _size)
    {
        Bind();
        width = (int)_size.x;
        height = (int)_size.y;
        std::cout << "Regenerating texture: " << width << "x" << height << std::endl;
        // Overwrite the texture buffer with an empty texture
        glTexImage2D( GL_TEXTURE_2D, 0, (int)GetInternalFormat(), (int)_size.x, (int)_size.y, 0, GetFormat(), GetDataType(), nullptr );
    }

    void Texture2D::Bind(uint32_t _slot) const
    {
        glActiveTexture(GL_TEXTURE0 + _slot);
        glBindTexture(GL_TEXTURE_2D, rendererID);
        slot = GL_TEXTURE0 + _slot;
    }

    void Texture2D::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture2D::SetData(void* _data, glm::vec2 _size)
    {
        Bind();
        width = (int)_size.x;
        height = (int)_size.y;
        // Overwrite the texture buffer with the given data
        glTexImage2D( GL_TEXTURE_2D, 0, (int)GetInternalFormat(), width, height, 0, GetFormat(), GetDataType(), _data );
    }

    uint32_t Texture2D::GetFormat() const
    {
        return (uint32_t)format;
    }

    uint32_t Texture2D::GetInternalFormat() const
    {
        return (uint32_t)internalFormat;
    }

    uint32_t Texture2D::GetDataType() const
    {
        switch (internalFormat)
        {
        case InternalTextureFormat::R8:
        case InternalTextureFormat::RG8:
        case InternalTextureFormat::RGB8:
        case InternalTextureFormat::RGBA8:
        case InternalTextureFormat::DEPTH24:
        case InternalTextureFormat::STENCIL8:
        case InternalTextureFormat::DEPTH24_STENCIL8:
            return GL_UNSIGNED_BYTE;
            break;
        case InternalTextureFormat::R16F:
        case InternalTextureFormat::R32F:
        case InternalTextureFormat::RG16F:
        case InternalTextureFormat::RG32F:
        case InternalTextureFormat::RGB16F:
        case InternalTextureFormat::RGB32F:
        case InternalTextureFormat::RGBA16F:
        case InternalTextureFormat::RGBA32F:
            return GL_FLOAT;
            break;
        }
    }

    void Texture2D::SetWrap(TextureWrap _wrap)
    {
        wrap = _wrap;
        Bind();
        uint32_t wrapMode = 0;
        switch (_wrap)
        {
        case TextureWrap::MIRRORED_REPEAT:
            wrapMode = GL_MIRRORED_REPEAT;
            break;
        case TextureWrap::REPEAT:
            wrapMode = GL_REPEAT;
            break;
        case TextureWrap::CLAMP_TO_EDGE:
            wrapMode = GL_CLAMP_TO_EDGE;
            break;
        case TextureWrap::CLAMP_TO_BORDER:
            wrapMode = GL_CLAMP_TO_BORDER;
            break;
        }
        // Set the wrap mode for both axes
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    }

    void Texture2D::SetFilter(TextureFilter _minFilter, TextureFilter _magFilter)
    {
        Bind();
        minFilter = _minFilter;
        magFilter = _magFilter;
        uint32_t minFilterMode = 0;
        uint32_t magFilterMode = 0;
        switch (_minFilter)
        {
        case TextureFilter::NEAREST:
            minFilterMode = GL_NEAREST;
            break;
        case TextureFilter::LINEAR:
            minFilterMode = GL_LINEAR;
            break;
        }
    
        switch (_magFilter)
        {
        case TextureFilter::NEAREST:
            magFilterMode = GL_NEAREST;
            break;
        case TextureFilter::LINEAR:
            magFilterMode = GL_LINEAR;
            break;
        }

        // Set the filter mode for both axes
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterMode );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterMode );
    }
}