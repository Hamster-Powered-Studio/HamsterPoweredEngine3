#shader vertex
#version 460 core

in vec3 vPos;
in vec3 vNormal;
in vec2 vTexCoord;
in vec4 vColour;

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
    //gl_Position = modelViewProjection * vec4(vPos, 1.0);
    gl_Position = vec4(vPos, 1.0);

    fPos = vec3(uModel * vec4(vPos, 1.0));
}



#shader fragment
#version 460 core

in vec3 fPos;
in vec3 fVertexNormal;
in vec2 fTexCoord;
in vec4 fColour;
in vec3 fWSNormal;

layout (location = 0) out vec4 gFragColour;
        
uniform sampler2D uDiffuse;
uniform vec4 uColour;
uniform float uTime;

void main() {

    vec3 normal = normalize(fWSNormal);
    vec3 col = mix(uColour.xyz, vec3(0.0, 0.0, 1), (sin(uTime * 5) + 1.0) / 2.0);
    gFragColour = vec4(col.xyz, 1.0);
}

