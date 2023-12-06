
#define MAX_POINT_LIGHTS 32
#define MAX_DIRECTIONAL_LIGHTS 4

struct PointLight
{
    vec3 Position;
    vec3 Colour;
    float Intensity;
    float Radius;
};

struct DirectionalLight
{
    vec3 Direction;
    vec3 Colour;
    float Intensity;
};


// calculate the colour of a point in the scene
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 position)
{
    vec3 lightDir = light.Position - position;
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
        diffuseColour = vec4(light.Colour * diffuseFactor * light.Intensity * attenuation, 1.0f);
    
    }
    return (diffuseColour).xyz;
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal)
{
    vec3 lightDir = normalize(-light.Direction);
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    //vec3 HalfwayVector = normalize(lightDir + viewDir);
    //float spec = pow(max(dot(normal, HalfwayVector), 0.0), 128.0f);

    return (diff * light.Colour) * light.Intensity;
}