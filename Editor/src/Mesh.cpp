#include "Mesh.h"

Ref<Mesh> Mesh::CreateCube()
{
    auto mesh = CreateRef<Mesh>();

    mesh->mVertices = {
        Vertex {
            { -0.5f, -0.5f, 0.5f },
            { -1.0f, -1.0f, 1.0f }
        },
        Vertex {
            { 0.5f, -0.5f, 0.5f },
            { 1.0f, -1.0f, 1.0f }
        },
        Vertex {
            { 0.5f, 0.5f, 0.5f },
            { 1.0f, 1.0f, 1.0f }
        },
        Vertex {
            { -0.5f, 0.5f, 0.5f },
            { -1.0f, 1.0f, 1.0f }
        },
        Vertex {
            { -0.5f, -0.5f, -0.5f },
            { -1.0f, -1.0f, -1.0f }
        },
        Vertex {
            { 0.5f, -0.5f, -0.5f },
            { 1.0f, -1.0f, -1.0f }
        },
        Vertex {
            { 0.5f, 0.5f, -0.5f },
            { 1.0f, 1.0f, -1.0f }
        },
        Vertex {
            { -0.5f, 0.5f, -0.5f },
            { -1.0f, 1.0f, -1.0f }
        }
    };

    mesh->mIndices = {
        0, 1, 2,
        2, 3, 0,
        1, 5, 6,
        6, 2, 1,
        7, 6, 5,
        5, 4, 7,
        4, 0, 3,
        3, 7, 4,
        4, 5, 1,
        1, 0, 4,
        3, 2, 6,
        6, 7, 3
    };

    return mesh;
}
