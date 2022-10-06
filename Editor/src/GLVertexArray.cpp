#include "GLVertexArray.h"

#include <glad/glad.h>

#include "Mesh.h"

GLVertexArray::GLVertexArray()
{
    glCreateVertexArrays(1, &mId);
}

GLVertexArray::~GLVertexArray()
{
    glDeleteBuffers(1, &mVertexId);
    glDeleteBuffers(1, &mIndexId);
    glDeleteVertexArrays(1, &mId);
}

void GLVertexArray::Bind()
{
    glBindVertexArray(mId);
}

void GLVertexArray::Unbind()
{
    glBindVertexArray(0);
}

void GLVertexArray::Render()
{
    glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_SHORT, nullptr);
}

Ref<GLVertexArray> GLVertexArray::Create(const Ref<Mesh>& mesh)
{
    auto va = CreateRef<GLVertexArray>();

    va->mVertexCount = std::size(mesh->GetVertices());
    va->mIndexCount = std::size(mesh->GetIndices());

    glBindVertexArray(va->mId);

    glCreateBuffers(1, &va->mVertexId);
    glBindBuffer(GL_ARRAY_BUFFER, va->mVertexId);
    glBufferData(GL_ARRAY_BUFFER, std::size(mesh->GetVertices()) * sizeof(Vertex), std::data(mesh->GetVertices()), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));

    glCreateBuffers(1, &va->mIndexId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, va->mIndexId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, std::size(mesh->GetIndices()) * sizeof(uint16), std::data(mesh->GetIndices()), GL_STATIC_DRAW);

    glBindVertexArray(0);

    return va;
}
