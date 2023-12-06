#shader vertex
#include "Resources/Shaders/WindowPlaneVS.glsl"


#shader fragment
#version 460 core

#include "Resources/Shaders/GBuffer.glsl"

uniform GBuffer uGBuffer;
uniform sampler2D uTexNoise;

uniform mat4 uView;
uniform mat4 uProjection;
uniform vec2 uResolution;

uniform vec3 uSamples[64];
uniform float uKernelSize = 64;
uniform float uRadius = 0.2;
uniform float uBias = 0.0;

in vec2 fTexCoord;

layout (location = 0) out float FragColor;

void main() {
    const vec2 noiseScale = vec2(uResolution.x / 4.0, uResolution.y / 4.0);
    
    vec3 normal = normalize(texture(uGBuffer.Normal, fTexCoord).rgb);
    vec3 fragPos = texture(uGBuffer.Position, fTexCoord).xyz;
    vec3 randVec = normalize(texture(uTexNoise, fTexCoord * noiseScale).xyz);
    
    vec3 tangent = normalize(randVec - normal * dot(randVec, normal));
    vec3 bitangent = cross(tangent, normal);
    mat3 TBN = mat3(tangent, bitangent, normal);
    
    float occlusion = 0.0;
    for (int i = 0; i < uKernelSize; ++i)
    {
        vec3 samplePos = TBN * uSamples[i].xyz;
        samplePos = fragPos + samplePos * uRadius;
        
        vec4 offset = vec4(samplePos, 1.0);
        offset = uProjection * offset;
        offset.xyz /= offset.w;
        offset.xyz = offset.xyz * 0.5 + 0.5;
        
        float sampleDepth = texture(uGBuffer.Position, offset.xy).z;
        
        float rangeCheck = smoothstep(0.0, 1.0, uRadius / abs(fragPos.z - sampleDepth));
        occlusion += (sampleDepth >= samplePos.z + uBias ? 1.0 : 0.0) * rangeCheck;
    }

    occlusion = 1.0 - (occlusion / uKernelSize);
    FragColor = pow(occlusion, 3);
}
