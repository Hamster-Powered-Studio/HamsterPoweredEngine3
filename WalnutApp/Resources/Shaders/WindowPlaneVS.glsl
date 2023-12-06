
#version 460 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec4 vColour;

uniform mat4 uModel;
uniform mat4 uViewProjection;

out vec2 fTexCoord;


void main() {
    fTexCoord = vTexCoord;

    // project across entire screen
    mat4 projection = mat4(1);

    mat4 modelViewProjection = uViewProjection * uModel;
    vec4 pos = projection * vec4(vPos, 0.5);

    gl_Position = pos;
}