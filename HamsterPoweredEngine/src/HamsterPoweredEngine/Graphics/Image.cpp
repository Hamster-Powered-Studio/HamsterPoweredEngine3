#include "Image.h"
#include <glad/gl.h>
#include <iostream>
#include "Texture.h"
#include <glm/glm.hpp>



#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

#include <fstream>

#include "stb_image.h"

namespace Hamster
{
    Image::Image(glm::vec2 _size, uint32_t _channels)
    {
        // Create empty image
        SetData(nullptr, (uint32_t)_size.x, (uint32_t)_size.y, _channels);
    }


    Image::Image(const std::string& _path)
    {
        // Load image from disk
        LoadImage(_path);
    }

    Image::Image(const Texture2D& _texture)
    {
        // Load image from texture
        width = _texture.GetWidth();
        height = _texture.GetHeight();
        channels = 4;

        // Change channels based on texture format
        auto format = _texture.GetFormat();
        if (format == GL_RED)
            channels = 1;
        else if (format == GL_RG)
            channels = 2;
        else if (format == GL_RGB)
            channels = 3;
        else if (format == GL_RGBA)
            channels = 4;

        // Get texture data from OpenGL
        data.reserve(width * height * channels);
        _texture.Bind();
        glGetTexImage(GL_TEXTURE_2D, 0, _texture.GetFormat(), GL_UNSIGNED_BYTE, data.data());
        
    }

    Image::~Image()
    {
        Clear();
    }

    void Image::LoadImage(const std::string& _path, bool _flipY)
    {
        // if path ends with .raw, use ImportRaw() instead as stb_image doesn't support raw images
        if (_path.substr(_path.find_last_of(".") + 1) == "raw")
        {
            ImportRaw(_path);
            return;
        }
        
        // Load image from disk using stb_image
        stbi_set_flip_vertically_on_load(_flipY);
        
        int _width, _height, _channels;
        unsigned char* _data = stbi_load(_path.c_str(), &_width, &_height, &_channels, 0);
        if (_data)
        {
            // Set image data
            SetData(_data, _width, _height, _channels);
        }
        else
        {
            std::cout << "Failed to load image: " << _path << std::endl;
        }
        std::cout << "Loaded image: " << _path << std::endl;
        stbi_image_free(_data);
    }

    void Image::SaveImage(const std::string& _path) //TODO: Implement
    {
        // Save image to disk
        stbi_write_png(_path.c_str(), width, height, channels, data.data(), width * channels);
    }

    void Image::Clear()
    {
        // Clear image data
        if (!data.empty())
        {
            data.clear();
        }
    }

    void Image::SetData(unsigned char* _data, uint32_t _width, uint32_t _height, uint32_t _channels)
    {
        // Clear image data
        Clear();
        // Set image data
        width = _width;
        height = _height;
        channels = _channels;
        data.reserve((width * height * channels));

        for (unsigned int i = 0; i < width * height * channels; i++)
        {
            data.push_back(_data[i]);
        }
    }

    void Image::ResampleChannels(uint32_t _channels)
    {
        uint32_t oldChannels = channels;
        channels = _channels;

        if (oldChannels == channels)
        {
            return;
        }

        // Resample image data
        std::vector<unsigned char> _newData;
        _newData.reserve(width * height * channels);
        for (unsigned int x = 0; x < width; x++)
        {
            for (unsigned int y = 0; y < height; ++y)
            {
                glm::vec4 _color = GetPixel(glm::vec2(x, y));
                for (unsigned int i = 0; i < channels; i++)
                {
                    _newData[x * channels + y * width * channels + i] = (unsigned char)(_color[(int)i] * 255);
                }
            }
        }

        Clear();
        data = _newData;
    }

    void Image::ImportRaw(const std::string& path)
    {
        width = 512;
        height = 512;
        channels = 1;
        data.resize(width * height * channels);
        std::ifstream _file(path, std::ios::binary);
        if (_file.is_open())
        {
            _file.read((char*)data.data(), width * height * channels);
            _file.close();
        }
        else
        {
            std::cout << "Failed to load image: " << path << std::endl;
        }
        
    }

    void Image::SetPixel(glm::vec2 _position, glm::vec4 _color)
    {
        // get pointer to pixel in the vector
        unsigned char* _pixel = &data[(int)_position.x * channels + (int)_position.y * width * channels];
        
        // set pixel color
        for (unsigned int i = 0; i < channels; i++)
        {
            _pixel[i] = (unsigned char)(_color[i] * 255);
        }
    }

    glm::vec4 Image::GetPixel(glm::vec2 _position) const
    {
        // get pointer to pixel. Each pixel has 1 byte per channel
        uint32_t _index = (int)_position.x * channels + (int)_position.y * width * channels;
        const unsigned char* _pixel = &data[_index];

        // get pixel color from pointer
        glm::vec4 _color = {0, 0, 0, 1};
        for (unsigned int i = 0; i < channels; i++)
        {
            _color[i] = (float)_pixel[i] / 255;
        }
        return _color;
    }

    glm::vec4 Image::GetUV(glm::vec2 _uv) const
    {
        float u = _uv.x;
        float v = _uv.y;

        // Get pixel from uv coordinates
        int x = (int)(u * (float)width);
        int y = (int)(v * (float)height);

        
        unsigned int x1 = x + 1;
        unsigned int y1 = y + 1;
    
        if (x1 >= width)
            x1 = width - 1;

        if (y1 >= height)
            y1 = height - 1;

        // Smoothly interpolate between pixels
        float xBlend = u * (float)width - x;
        float yBlend = v * (float)height - y;
        glm::vec4 top = (1 - xBlend) * GetPixel({x, y}) + xBlend * GetPixel({x1, y});
        glm::vec4 bottom = (1 - xBlend) * GetPixel({x, y1}) + xBlend * GetPixel({x1, y1});
        
        return (1 - yBlend) * top + yBlend * bottom;

    
    }
}