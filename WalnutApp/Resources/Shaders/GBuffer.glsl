
// glsl g buffer spec
// 0:diffuse
// 1:normal
// 2:position
// 3:specular
// 4:emission
// 5:depth

// glsl gbuffer struct
struct GBuffer
{
    sampler2D diffuse;
    sampler2D normal;
    sampler2D position;
    sampler2D specular;
    sampler2D emission;
    sampler2D depth;
    
};

