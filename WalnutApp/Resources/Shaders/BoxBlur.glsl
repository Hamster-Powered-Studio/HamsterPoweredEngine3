#shader vertex
#include "Resources/Shaders/WindowPlaneVS.glsl"

#shader fragment
#version 460 core

in vec2 fTexCoord;
out float FragColour;

uniform sampler2D uSSAOInput;

void main()
{
    vec2 texelSize = 1.0 / vec2(textureSize(uSSAOInput, 0));
    float result = 0.0;
    for (int x = -2; x < 2; ++x)
    {
        for (int y = -2; y < 2; ++y)
        {
            vec2 offset = vec2(float(x), float(y)) * texelSize;
            result += texture(uSSAOInput, fTexCoord + offset).r;
        }
    }
    FragColour = result / (4.0 * 4.0);
}  