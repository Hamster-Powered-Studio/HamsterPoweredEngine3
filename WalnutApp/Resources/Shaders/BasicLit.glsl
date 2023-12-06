#shader vertex
#version 460 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec4 vColour;

out vec3 fPos;
out vec3 fVertexNormal;
out vec2 fTexCoord;
out vec4 fColour;
out vec3 fWSNormal;

uniform mat4 uModel;
uniform mat4 uViewProjection;


void main() {
    fTexCoord = vTexCoord;
    fColour = vColour;

    fVertexNormal = normalize(vNormal);
    fWSNormal = vec3(mat4(transpose(inverse(uModel))) * vec4(vNormal, 1.0));

    mat4 modelViewProjection = uViewProjection * uModel;
    gl_Position = modelViewProjection * vec4(vPos, 1.0);
    
    fPos = vec3(uModel * vec4(vPos, 1.0));
}



#shader fragment
#version 460 core
#include "Resources/Shaders/LightDefinitions.glsl"

uniform PointLight uPointLights[MAX_POINT_LIGHTS];
uniform DirectionalLight uDirectionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform float uDirectionalLightCount;
uniform float uPointLightCount;

in vec3 fPos;
in vec3 fVertexNormal;
in vec2 fTexCoord;
in vec4 fColour;
in int fTextureIndex;
in vec3 fWSNormal;

layout (location = 0) out vec4 gFragColour;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gPosition;
layout (location = 3) out vec4 gSpecular;
layout (location = 4) out vec4 gEmission;
layout (location = 5) out vec4 gDepth;

uniform sampler2D uDiffuse;


void main() {
    
    vec3 normal = normalize(fWSNormal);
    
    //vec4 diffuse = texture(uDiffuse, fTexCoord);

    vec4 albedo = vec4(1, 1, 1, 1);

    //calculate all point lights
    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    //calculate ambient
    ambient = 0.1 * albedo.xyz;

    //calculate diffuse and specular
    vec3 light = vec3(0, 0, 0);
    for (int i = 0; i < uPointLightCount; i++)
    {
        if (uPointLights[i].Intensity > 0.0)
        {
            light += CalculatePointLight(uPointLights[i], normal, fPos);
        }
    }

    diffuse = light * albedo.xyz;

    vec4 result = vec4(ambient + diffuse + specular, 1.0);
    
    gFragColour = vec4(result.xyz, 1.0);
    gNormal = vec4(normal, 1.0);
    gPosition = vec4(fPos, 1.0);
    gEmission = vec4(0, 0, 0, 0);
    gSpecular = vec4(0, 0, 0, 0);
}

