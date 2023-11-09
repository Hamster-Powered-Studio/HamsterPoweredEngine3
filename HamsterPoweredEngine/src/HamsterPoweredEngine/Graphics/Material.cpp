#include "Material.h"

#include <iostream>
#include <ostream>

#include "ShaderLoader.h"

namespace Hamster
{
    Material::Material()
    {
    }

    Material::Material(GLHandle<Shader> _shader)
    {
        // If no shader is provided, load the default shader
        if (!_shader.IsValid())
        {
            shader = ShaderLoader::Load("Resources/Shaders/Default.glsl");
        }
        else
        {
            shader = _shader;
        }
    }


    void Material::SetParameter(const std::string& name, const MaterialParameter& parameter)
    {
        parameters.insert_or_assign(name, parameter);
    }

    MaterialParameter& Material::operator[](const std::string& name)
    {
        // If the parameter doesn't exist, create it
        if (parameters.find(name) == parameters.end())
        {
            parameters.insert_or_assign(name, MaterialParameter(0.f));
        }
        // Return the parameter
        auto param = parameters.find(name);
        return param->second;
    }

    Material::~Material()
    {
    }

    void Material::Apply()
    {
        // Bind the shader
        auto shaderRef = shader.Get();
        shaderRef->Bind();

        // Keep track of how many textures we've bound, as they can be bound to any texture unit
        int textureIndex = 0;
        for (auto& parameter : parameters)
        {
            std::string name = parameter.first;
            auto& value = parameter.second;

            // Set the uniform based on the type
            switch (value.type)
            {
            case MaterialParameter::Type::Float: shaderRef->SetUniform1f(name, value.floatValue); break;
            case MaterialParameter::Type::Vec2: shaderRef->SetUniform2f(name, value.vec2Value.x, value.vec2Value.y); break;
            case MaterialParameter::Type::Vec3: shaderRef->SetUniform3f(name, value.vec3Value.x, value.vec3Value.y, value.vec3Value.z); break;
            case MaterialParameter::Type::Vec4: shaderRef->SetUniform4f(name, value.vec4Value.x, value.vec4Value.y, value.vec4Value.z, value.vec4Value.w); break;
            case MaterialParameter::Type::Mat4: shaderRef->SetUniformMat4f(name, value.mat4Value); break;
            case MaterialParameter::Type::Sampler2D: 
                value.sampler2DValue->Bind(textureIndex);
                shaderRef->SetUniform1i(name, textureIndex);
                textureIndex++;
                break;
            
            default:
                std::cout << "Unknown type: " << name << std::endl; break;
            }
        }
    
    }

    Material* Material::DefaultMaterial()
    {
        if (defaultMaterial == nullptr)
        {
            defaultMaterial = new Material(ShaderLoader::Load("Resources/Shaders/Default.glsl")); //TODO: dont
        }
        return defaultMaterial;
    }
}