
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
    sampler2D Diffuse;
    sampler2D Normal;
    sampler2D Position;
    sampler2D Specular;
    sampler2D Emission;
    sampler2D Depth;
    
};

