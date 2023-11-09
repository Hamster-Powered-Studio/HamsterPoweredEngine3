#include "Shader.h"



#include <iostream>
#include <ostream>

#include <glm/mat4x4.hpp>

#include <glad/gl.h>

namespace Hamster
{
    Shader::Shader(const ShaderProgramSource& _source)
    {
        int success;
        char infoLog[512];

        // Vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char* vertexSource = _source.VertexSource.c_str();
        glShaderSource(vertexShader, 1, &vertexSource, nullptr);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        } 

        // Geometry shader
        unsigned int geometryShader = 0;
        if (!_source.GeometrySource.empty())
        {
            geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
            const char* geometrySource = _source.GeometrySource.c_str();
            glShaderSource(geometryShader, 1, &geometrySource, nullptr);
            glCompileShader(geometryShader);
            glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(geometryShader, 512, nullptr, infoLog);
                std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        }

        unsigned int tessellationControlShader = 0;
        if (!_source.TessellationControlSource.empty())
        {
            tessellationControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
            const char* tessellationControlSource = _source.TessellationControlSource.c_str();
            glShaderSource(tessellationControlShader, 1, &tessellationControlSource, nullptr);
            glCompileShader(tessellationControlShader);
            glGetShaderiv(tessellationControlShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(tessellationControlShader, 512, nullptr, infoLog);
                std::cout << "ERROR::SHADER::TESSELLATION_CONTROL::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        }

        unsigned int tessellationEvaluationShader = 0;
        if (!_source.TessellationEvaluationSource.empty())
        {
            tessellationEvaluationShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
            const char* tessellationEvaluationSource = _source.TessellationEvaluationSource.c_str();
            glShaderSource(tessellationEvaluationShader, 1, &tessellationEvaluationSource, nullptr);
            glCompileShader(tessellationEvaluationShader);
            glGetShaderiv(tessellationEvaluationShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(tessellationEvaluationShader, 512, nullptr, infoLog);
                std::cout << "ERROR::SHADER::TESSELLATION_EVALUATION::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        }
        
        // Fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragmentSource = _source.FragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        
        // Shader program
        rendererID = glCreateProgram();
        glAttachShader(rendererID, vertexShader);
        if (!_source.GeometrySource.empty())
        {
            glAttachShader(rendererID, geometryShader);
        }
        if (!_source.TessellationControlSource.empty())
        {
            glAttachShader(rendererID, tessellationControlShader);
        }
        if (!_source.TessellationEvaluationSource.empty())
        {
            glAttachShader(rendererID, tessellationEvaluationShader);
        }
        glAttachShader(rendererID, fragmentShader);
        glLinkProgram(rendererID);
        glGetProgramiv(rendererID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(rendererID, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // Delete shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        if (!_source.GeometrySource.empty())
        {
            glDeleteShader(geometryShader);
        }
        if (!_source.TessellationControlSource.empty())
        {
            glDeleteShader(tessellationControlShader);
        }
        if (!_source.TessellationEvaluationSource.empty())
        {
            glDeleteShader(tessellationEvaluationShader);
        }
        std::cout << "Shader made" << std::endl;
        
    }

    Shader::~Shader()
    {
        glDeleteProgram(rendererID);
        std::cout << "Shader gone" << std::endl;
    }

    void Shader::Bind() const
    {
        glUseProgram(rendererID);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    void Shader::SetUniform1i(const std::string& _name, int _value)
    {
        glUniform1i(GetUniformLocation(_name), _value);
    }

    void Shader::SetUniform1f(const std::string& _name, float _value)
    {
        glUniform1f(GetUniformLocation(_name), _value);
    }

    void Shader::SetUniform2f(const std::string& _name, float _v0, float _v1)
    {
        glUniform2f(GetUniformLocation(_name), _v0, _v1);
    }

    void Shader::SetUniform3f(const std::string& _name, float _v0, float _v1, float _v2)
    {
        glUniform3f(GetUniformLocation(_name), _v0, _v1, _v2);
    }

    void Shader::SetUniform4f(const std::string& _name, float _v0, float _v1, float _v2, float _v3)
    {
        glUniform4f(GetUniformLocation(_name), _v0, _v1, _v2, _v3);
    }

    void Shader::SetUniformMat4f(const std::string& _name, const glm::mat4& _data)
    {
        glUniformMatrix4fv(GetUniformLocation(_name), 1, GL_FALSE, &_data[0][0]);
    }

    int Shader::GetUniformLocation(const std::string& name)
    {
        // If the uniform location is already cached, return it
        if (uniformLocationCache.find(name) != uniformLocationCache.end())
        {
            return uniformLocationCache[name];
        }

        // Otherwise, get the uniform location and cache it
        int location = glGetUniformLocation(rendererID, name.c_str());
        if(location == -1)
        {
            std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
        }
        uniformLocationCache[name] = location;
        return location;
    }

}

