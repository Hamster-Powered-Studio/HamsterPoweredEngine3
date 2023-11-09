#include "ShaderLoader.h"

#include <fstream>
#include <iostream>

#include "Shader.h"

namespace Hamster
{
    GLHandle<Shader> ShaderLoader::Load(const std::string& path)
    {
        // check if the shader is already loaded
        if (cache.find(path) != cache.end())
        {
            if (auto shader = cache[path])
            {
                if (shader.IsValid())
                {
                    return shader;
                }
                
            }
        }

        std::string includeIdentifier = "#include ";
    
        Shader::ShaderProgramSource shaderSource;

        // Open the shader file
        std::ifstream shaderFile(path);
        if (!shaderFile)
        {
            std::cout << "Shader file not found: " << path << std::endl;
        }
    
        // Keep track of which shader source buffer we are writing into
        enum class ShaderType
        {
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1,
            GEOMETRY = 2,
            TESS_CONTROL = 3,
            TESS_EVALUATION = 4
        };
    
        // if there is no #shader line, fail
        ShaderType type = ShaderType::NONE;
        std::string line;
        while (std::getline(shaderFile, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                {
                    type = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos)
                {
                    type = ShaderType::FRAGMENT;
                }
                else if (line.find("geometry") != std::string::npos)
                {
                    type = ShaderType::GEOMETRY;
                }
                else if (line.find("tesc") != std::string::npos)
                {
                    type = ShaderType::TESS_CONTROL;
                }
                else if (line.find("tese") != std::string::npos)
                {
                    type = ShaderType::TESS_EVALUATION;
                }
                else
                {
                    std::cout << "Invalid shader type" << std::endl;
                }
            }
            else
            {
                // Add the line to the appropriate shader source buffer
                switch (type)
                {
                case ShaderType::VERTEX:
                    shaderSource.VertexSource += line + "\n";
                    break;
                case ShaderType::FRAGMENT:
                    shaderSource.FragmentSource += line + "\n";
                    break;
                case ShaderType::GEOMETRY:
                    shaderSource.GeometrySource += line + "\n";
                    break;
                case ShaderType::TESS_CONTROL:
                    shaderSource.TessellationControlSource += line + "\n";
                    break;
                case ShaderType::TESS_EVALUATION:
                    shaderSource.TessellationEvaluationSource += line + "\n";
                    break;
                case ShaderType::NONE:
                    std::cout << "Shader file " << path << " is missing a #shader line" << std::endl;
                    break;
                default:
                    std::cout << "Invalid shader type" << std::endl;
                    break;
                }
            }
        }

        // Preprocess the shader source for includes
        PreprocessShader(shaderSource.VertexSource, {});
        PreprocessShader(shaderSource.FragmentSource, {});
        PreprocessShader(shaderSource.GeometrySource, {});
        PreprocessShader(shaderSource.TessellationControlSource, {});
        PreprocessShader(shaderSource.TessellationEvaluationSource, {});
        
        auto handle = GraphicsResourceManager::ConstructObject<Shader>(shaderSource);
        cache[path] = handle;

        std::cout << "Successfully loaded shader: " << path << std::endl;
        
        return handle;
    
    }

    void ShaderLoader::PreprocessShader(std::string& source, std::vector<std::string>* includedPaths)
    {
        std::vector<std::string> paths;
        if (includedPaths == nullptr)
        {
            includedPaths = &paths;
        }
    
        // Find all #include statements
        size_t pos = source.find("#include");
        while (pos != std::string::npos)
        {
            // Find the start of the include path
            size_t start = source.find("\"", pos);
            if (start == std::string::npos)
            {
                std::cout << "Invalid include statement" << std::endl;
            }
            // Find the end of the include path
            size_t end = source.find("\"", start + 1);
            if (end == std::string::npos)
            {
                std::cout << "Invalid include statement" << std::endl;
            }
        
            // Extract the include path
            std::string includePath = source.substr(start + 1, end - start - 1);

            // If the include path is already in the list of included paths, skip it
            if (std::find(includedPaths->begin(), includedPaths->end(), includePath) != includedPaths->end())
            {
                pos = source.find("#include", pos + 1);
                continue;
            }
        
            // Load the include file
            std::string includeSource = GetFileContents(includePath);
        
            // Recursively preprocess the include file
            PreprocessShader(includeSource, includedPaths);
        
            // Replace the include statement with the include file
            source.replace(pos, end - pos + 1, includeSource);
        
            // Add the include path to the list of included paths
            includedPaths->push_back(includePath);
        
            // Find the next include statement
            pos = source.find("#include", pos + 1);
        }
    }

    std::string ShaderLoader::GetFileContents(const std::string& path)
    {
        std::string buffer;
        std::ifstream file(path);
        if (!file.is_open())
        {
            std::cout << "Shader include not found: " << path << std::endl;
        }

        // Read the file into a string
        file.seekg(0, std::ios::end);
        buffer.reserve(file.tellg());
        file.seekg(0, std::ios::beg);
        buffer.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return buffer;

    
    }
}