#pragma once

#include "Core.h"

#include <vector>
#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
};

class Mesh
{
public:
    Mesh() = default;

    const std::vector<Vertex>& GetVertices() const { return mVertices; }
    const std::vector<uint16>& GetIndices() const { return mIndices; }

    static Ref<Mesh> CreateCube();

private:
    std::vector<Vertex> mVertices;
    std::vector<uint16> mIndices;
};
