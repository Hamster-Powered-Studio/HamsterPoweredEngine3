#include "Plane.h"

namespace Hamster
{
    // Plane vertices, on the XY plane
    std::vector<Vertex> verts =
                {
        {{-0.5f, -0.5f, 0.0f}, {0, 0, 1}, {0, 0}, {1, 1, 1, 1}},
        {{0.5f, -0.5f, 0.0f}, {0, 0, 1}, {1, 0}, {1, 1, 1, 1}},
        {{0.5f, 0.5f, 0.0f}, {0, 0, 1}, {1, 1}, {1, 1, 1, 1}},
        {{-0.5f, 0.5f, 0.0f}, {0, 0, 1}, {0, 1}, {1, 1, 1, 1}}
                };

    std::vector<uint32_t> indices =
        {
        2, 3, 0,
        0, 1, 2
    };


    Plane::Plane() : Mesh(verts, indices)
    {
    }



}
