#pragma once

#include "Core.h"

class Mesh;

class GLVertexArray
{
public:
    GLVertexArray();
    ~GLVertexArray();

    void Bind();
    void Unbind();

    void Render();

    static Ref<GLVertexArray> Create(const Ref<Mesh>& mesh);

private:
    uint32 mId = 0;

    uint32 mVertexId = 0;
    uint32 mVertexCount = 0;

    uint32 mIndexId = 0;
    uint32 mIndexCount = 0;
};
