#shader vertex
#version 460 core

#include "Resources/Shaders/CommonVertexIO.glsl"

uniform mat4 uModel;
uniform mat4 uViewProjection;



void main() {
    fPos = vPos;
    fNormal = vNormal;
    fTexCoord = vTexCoord;
    fColour = vColour;
    fTextureIndex = vTextureIndex;

    // project across entire screen
    mat4 projection = mat4(1);

    mat4 modelViewProjection = uViewProjection * uModel;
    vec4 pos = projection * vec4(vPos, 0.5);

    gl_Position = pos;
}


#shader fragment
#version 460 core

#include "Resources/Shaders/VectorMath.glsl"
#include "Resources/Shaders/LightDefinitions.glsl"

in vec3 fPos;
in vec3 fNormal;
in vec2 fTexCoord;
in vec4 fColour;
flat in int fTextureIndex;

uniform PointLight uPointLights[MAX_POINT_LIGHTS];

#include "Resources/Shaders/CommonUniforms.glsl"

layout (location = 0) out vec4 FragColor;


void main() {
    // lighting pass    

    vec4 albedo = texture(uGBuffer.diffuse, fTexCoord);
    vec3 normal = texture(uGBuffer.normal, fTexCoord).rgb;
    vec3 position = texture(uGBuffer.position, fTexCoord).rgb;
    
    
    if (albedo.a < 0.1) {
        discard;
    }
    

        //calculate all point lights
        vec3 ambient = vec3(0.0);
        vec3 diffuse = vec3(0.0);
        vec3 specular = vec3(0.0);

        //calculate ambient
        ambient = 0.1 * albedo.xyz;

        //calculate diffuse and specular
        vec3 light = vec3(0, 0, 0);
        for (int i = 0; i < MAX_POINT_LIGHTS; i++)
        {
            if (uPointLights[i].intensity > 0.0)
            {
                light += CalculatePointLight(uPointLights[i], normal, position);
            }
        }

        diffuse = light * albedo.xyz;

        vec4 result = vec4(ambient + diffuse + specular, 1.0);

        FragColor = vec4(result.xyz, 1.0);

    

    
    
}
