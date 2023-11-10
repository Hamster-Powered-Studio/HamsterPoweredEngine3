#shader vertex
#version 460 core

in vec3 vPos;
in vec3 vNormal;
in vec2 vTexCoord;
in vec4 vColour;

out vec3 fPos;
out vec3 fNormal;
out vec2 fTexCoord;
out vec4 fColour;

uniform mat4 uModel;
uniform mat4 uViewProjection;


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

in vec3 fPos;
in vec3 fNormal;
in vec2 fTexCoord;
in vec4 fColour;

uniform sampler2D uTexture;

out vec4 colour;

void main() {
vec4 texColour = fColour;
texColour = texture(uTexture, fTexCoord);

float luminance = dot(texColour.rgb, vec3(0.2126, 0.7152, 0.0722));
texColour.rgb = vec3(luminance);
        
colour = texColour;

}

