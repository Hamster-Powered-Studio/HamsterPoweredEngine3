#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "GraphicsResourceManager.h"


namespace Hamster
{
    class Shader;

    // Shader loader. This is used to load shaders from files. It also caches shaders to avoid loading the same shader multiple times
    // The shader files are preprocessed to allow for #include directives
    // All shader components should be located in one file, denoted by:
    // #shader vertex
    // #shader fragment
    // #shader geometry
    // #shader tesc
    // #shader tese
    class ShaderLoader
    {
    public:
        // Load a shader from a file
        static GLHandle<Shader> Load(const std::string& path);
    
    protected:
        // Get the contents of a file as a string buffer
        static std::string GetFileContents(const std::string& string);

        // Recursively preprocess a shader file to allow for #include directives. Included paths are used to avoid circular includes
        static void PreprocessShader(std::string& source, std::vector<std::string>* includedPaths = {});
        
        // Shader cache to avoid loading the same shader multiple times
        static inline std::unordered_map<std::string, GLHandle<Shader>> cache;

    };
}
