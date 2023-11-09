#pragma once
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace Hamster
{
    class Texture2D;


    // Image data stored on the CPU side. This is the data that is loaded from disk, and can be read/written to.
    // Can be used to create a texture, can be created from a texture. Can be saved to disk.
    class Image
    {
    public:
        // Create an empty image (null data)
        Image(glm::vec2 _size, uint32_t _channels = 4);

        // Load image from disk
        Image(const std::string& _path);

        // Load image from texture
        Image(const Texture2D& _texture);

        // Dtor
        ~Image();

        // Load image from disk
        void LoadImage(const std::string& _path, bool _flipY = true);

        // Save image to disk
        void SaveImage(const std::string& _path);

        // Clear image data. This will delete the data array. It will not clear the image size or channels.
        void Clear();

        // Set the colour value of a given pixel
        void SetPixel(glm::vec2 _position, glm::vec4 _color);

        // Get the colour value of a given pixel
        glm::vec4 GetPixel(glm::vec2 _position) const;

        // Get the colour value of a given UV coordinate
        glm::vec4 GetUV(glm::vec2 _uv) const;

        // Set the raw image data
        void SetData(unsigned char* _data, uint32_t _width, uint32_t _height, uint32_t _channels);

        // Get the raw image data
        const std::vector<unsigned char>& GetData() const { return data; }
    
        uint32_t GetWidth() const { return width; }
        uint32_t GetHeight() const { return height; }
        uint32_t GetChannels() const { return channels; }

        // Change the number of channels in the image. This will resample the image data. This operation is destructive.
        void ResampleChannels(uint32_t _channels);

    
    private:
        void ImportRaw(const std::string& path);

        
        uint32_t width = 0;
        uint32_t height = 0;
        uint32_t channels = 0;
        std::vector<unsigned char> data;
    };
}