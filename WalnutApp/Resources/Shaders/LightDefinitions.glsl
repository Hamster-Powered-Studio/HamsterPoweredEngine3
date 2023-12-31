﻿
#define MAX_POINT_LIGHTS 32

struct PointLight
{
    vec3 position;
    vec3 colour;
    float intensity;
};

struct DirectionalLight
{
    vec3 direction;
    vec3 colour;
    float intensity;
};


// calculate the colour of a point in the scene
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 position)
{
    vec3 lightDir = light.position - position;
    float distance = length(lightDir);
    lightDir = normalize(lightDir);
    float diffuseFactor = dot(lightDir, normalize(normal));
    
    vec4 diffuseColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec4 specularColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    
    float constant = 1.0f;
    float linear = 0.7f;
    float quadratic = 1.8f;
    
    float attenuation = 1.0f / (constant + linear * distance + quadratic * (distance * distance));
    
    // diffuse
    if (diffuseFactor > 0.0f)
    {
        diffuseColour = vec4(light.colour * diffuseFactor * light.intensity * attenuation, 1.0f);
    
    }
    
    return (diffuseColour).xyz;
    
}