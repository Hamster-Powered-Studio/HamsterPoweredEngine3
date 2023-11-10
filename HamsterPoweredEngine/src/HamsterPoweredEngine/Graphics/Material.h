#pragma once
#include <map>

#include "Shader.h"
#include "Texture.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "GraphicsResourceManager.h"

namespace Hamster
{
    // A material parameter is a value that can be passed to a shader
    // It can be a float, a vector, a matrix or a texture
    // It is used to set the value of a uniform in a shader
    struct MaterialParameter
    {
        enum class Type
        {
            Float,
            Vec2,
            Vec3,
            Vec4,
            Mat4,
            Sampler2D
        };
    
        union
        {
            float floatValue;
            glm::vec2 vec2Value;
            glm::vec3 vec3Value;
            glm::vec4 vec4Value;
            glm::mat4 mat4Value;
            GLHandle<Texture2D> sampler2DValue = {};
        };

        Type type;

        // Constructors for each type
        MaterialParameter(float _value) : type(Type::Float), floatValue(_value) {}
        MaterialParameter(glm::vec2 _value) : type(Type::Vec2), vec2Value(_value) {}
        MaterialParameter(glm::vec3 _value) : type(Type::Vec3), vec3Value(_value) {}
        MaterialParameter(glm::vec4 _value) : type(Type::Vec4), vec4Value(_value) {}
        MaterialParameter(glm::mat4 _value) : type(Type::Mat4), mat4Value(_value) {}
        MaterialParameter(GLHandle<Texture2D> _value) : type(Type::Sampler2D)
        {
            sampler2DValue = _value;
        }

        // Destructor. Texture ref needs to be cleared manually or else it will stay in memory forever
        ~MaterialParameter()
        {
            if (type == Type::Sampler2D)
            {
                sampler2DValue.Get()->Unbind();
                sampler2DValue = GLHandle<Texture2D>();
            }
        }
        MaterialParameter(const MaterialParameter& other) : type(other.type)
        {
            switch (type)
            {
            case Type::Float: floatValue = other.floatValue; break;
            case Type::Vec2: vec2Value = other.vec2Value; break;
            case Type::Vec3: vec3Value = other.vec3Value; break;
            case Type::Vec4: vec4Value = other.vec4Value; break;
            case Type::Mat4: mat4Value = other.mat4Value; break;
            case Type::Sampler2D: sampler2DValue = other.sampler2DValue; break;
            default: break;
            }
        }
        MaterialParameter& operator=(const MaterialParameter& other)
        {
            type = other.type;
            switch (type)
            {
            case Type::Float: floatValue = other.floatValue; break;
            case Type::Vec2: vec2Value = other.vec2Value; break;
            case Type::Vec3: vec3Value = other.vec3Value; break;
            case Type::Vec4: vec4Value = other.vec4Value; break;
            case Type::Mat4: mat4Value = other.mat4Value; break;
            case Type::Sampler2D: sampler2DValue = other.sampler2DValue; break;
            default: break;
            }
            return *this;
        }
    };

    // A material is a collection of parameters and a shader
    // Applying a material will set all the parameters in the shader
    class Material
    {
    public:
        // Create a material that uses a shader
        Material(GLHandle<Shader> _shader);

        Material(const Material& other);

        // Set a parameter in the material by name. Can take a float, a vector, a matrix or a texture
        void SetParameter(const std::string& name, const MaterialParameter& parameter);

        // Get a parameter in the material by name
        MaterialParameter& operator[](const std::string& name);
        ~Material();

        // Apply the material. This will bind the shader and set all the parameters in the shader
        void Apply() const;

        // Get the default material. This material is used when no material is set
        static Material* DefaultMaterial();

        operator bool() {return shader.Get() != nullptr;}
    private:
        GLHandle<Shader> shader;
        std::map<std::string, MaterialParameter> parameters;
    
        inline static Material* defaultMaterial = {};
    };
}
