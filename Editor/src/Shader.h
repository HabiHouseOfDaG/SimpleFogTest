#pragma once

#include "Core.h"

#include <filesystem>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader();
    ~Shader();

    void Bind();
    void Unbind();

    void SetUniform(const char* const name, const f32 f);
    void SetUniform(const char* const name, const glm::vec3& v);
    void SetUniform(const char* const name, const glm::vec4& v);
    void SetUniform(const char* const name, const glm::mat4& m);

    static Ref<Shader> Create(const std::filesystem::path& vert, const std::filesystem::path& frag);
    static uint32 CompileShader(const uint32 type, const std::filesystem::path& shaderFile);

private:
    uint32 mId = 0;
};
