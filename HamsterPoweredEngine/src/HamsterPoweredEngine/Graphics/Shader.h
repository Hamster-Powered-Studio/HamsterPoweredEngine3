#pragma once
#include <string>
#include <unordered_map>

#include <glm/mat4x4.hpp>

namespace Hamster
{
    // Shader program. This is a wrapper around OpenGL's shader program. It is used to load shaders and set uniforms
    class Shader
    {
    public:
        struct ShaderProgramSource
        {
            std::string VertexSource;
            std::string FragmentSource;
            std::string GeometrySource;
            std::string TessellationControlSource;
            std::string TessellationEvaluationSource;
        };

        // Load a shader from a selection of source buffers
        Shader(const ShaderProgramSource& _source);
        ~Shader();

        // Bind the shader for use
        void Bind() const;
        // Unbind the shader from use
        void Unbind() const;

        // Set a uniform integer value
        void SetUniform1i(const std::string& _name, int _value);

        // Set a uniform float value
        void SetUniform1f(const std::string& _name, float _value);

        // Set a uniform 2D vector value
        void SetUniform2f(const std::string& _name, float _v0, float _v1);

        // Set a uniform 3D vector value
        void SetUniform3f(const std::string& _name, float _v0, float _v1, float _v2);

        // Set a uniform 4D vector value
        void SetUniform4f(const std::string& _name, float _v0, float _v1, float _v2, float _v3);

        // Set a uniform 4x4 matrix value
        void SetUniformMat4f(const std::string& _name, const glm::mat4& _data);

        // Get the location of a uniform in the shader
        int GetUniformLocation(const std::string& name);

    private:
        uint32_t rendererID = 0;
        
        // Cache for uniform locations to avoid glGetUniformLocations
        std::unordered_map<std::string, int> uniformLocationCache = {};
    
    };

}
