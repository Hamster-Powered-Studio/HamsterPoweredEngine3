#shader vertex
#version 460 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec4 vColour;

uniform mat4 uModel;
uniform mat4 uViewProjection;

out vec3 fPos;
out vec3 fNormal;
out vec2 fTexCoord;
out vec4 fColour;

void main() {
    fPos = vPos;
    fNormal = vNormal;
    fTexCoord = vTexCoord;
    fColour = vColour;

    // project across entire screen
    mat4 projection = mat4(1);

    mat4 modelViewProjection = uViewProjection * uModel;
    vec4 pos = projection * vec4(vPos, 0.5);

    gl_Position = pos;
}


#shader fragment
#version 460 core


#include "Resources/Shaders/LightDefinitions.glsl"
#include "Resources/Shaders/GBuffer.glsl"

in vec3 fPos;
in vec3 fNormal;
in vec2 fTexCoord;
in vec4 fColour;

uniform PointLight uPointLights[MAX_POINT_LIGHTS];
uniform DirectionalLight uDirectionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform GBuffer uGBuffer;
uniform float uPointLightCount;
uniform float uDirectionalLightCount;
uniform mat4 uView;
uniform mat4 uProjection;
uniform vec2 uResolution;
uniform sampler2D uSSAO;


layout (location = 0) out vec4 FragColor;


void main() {
    // lighting pass    

    vec4 albedo = texture(uGBuffer.Diffuse, fTexCoord);
    vec3 normal = texture(uGBuffer.Normal, fTexCoord).rgb;
    vec3 position = texture(uGBuffer.Position, fTexCoord).rgb;

    float AmbientOcclusion = texture(uSSAO, fTexCoord).r;


    if (albedo.a < 0.1) {
        discard;
    }
    

        //calculate all point lights
        vec3 ambient = vec3(0.1 * albedo * AmbientOcclusion);
        vec3 diffuse = vec3(0.0);
        vec3 specular = vec3(0.0);
        vec3 viewDir = normalize(-position);

        //calculate diffuse and specular
        vec3 pointLight = vec3(0, 0, 0);
        for (int i = 0; i < uPointLightCount; i++)
        {
            pointLight += CalculatePointLight(uPointLights[i], normal, position);
        }

        vec3 dirLight = vec3(0, 0, 0);
        for (int i = 0; i < uDirectionalLightCount; i++)
        {
            dirLight += CalculateDirectionalLight(uDirectionalLights[i], normal);
        }

        diffuse = (pointLight + dirLight) * albedo.xyz;

        vec4 result = vec4(ambient + diffuse + specular, 1.0);
        FragColor = vec4(result.xyz, 1.0);
    
}
