#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <fstream>
#include <vector>

#include "Log.h"

Shader::Shader() :
    mId(glCreateProgram())
{}

Shader::~Shader()
{
    glDeleteProgram(mId);
}

void Shader::Bind()
{
    glUseProgram(mId);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::SetUniform(const char* const name, const glm::vec4& v)
{
    glUniform4f(glGetUniformLocation(mId, name), v.x, v.y, v.z, v.w);
}

void Shader::SetUniform(const char* const name, const glm::mat4& m)
{
    glUniformMatrix4fv(glGetUniformLocation(mId, name), 1, GL_FALSE, glm::value_ptr(m));
}

Ref<Shader> Shader::Create(const std::filesystem::path& vert, const std::filesystem::path& frag)
{
    auto vertShader = CompileShader(GL_VERTEX_SHADER, vert);
    if (vertShader == 0)
        return nullptr;

    auto fragShader = CompileShader(GL_FRAGMENT_SHADER, frag);
    if (fragShader == 0)
    {
        glDeleteShader(vertShader);
        return nullptr;
    }

    auto shader = CreateRef<Shader>();

    glAttachShader(shader->mId, vertShader);
    glAttachShader(shader->mId, fragShader);
    glLinkProgram(shader->mId);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    GLint isLinked = 0;
    glGetProgramiv(shader->mId, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(shader->mId, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(shader->mId, maxLength, &maxLength, std::data(infoLog));

        shader = nullptr;

        LOG_ERROR("Failed to link shader program: {0}", std::data(infoLog));
    }

    return shader;
}

uint32 Shader::CompileShader(const uint32 type, const std::filesystem::path& shaderFile)
{
    std::fstream file(shaderFile);
    if (!file)
    {
        LOG_ERROR("Failed to open shader file {0}", shaderFile.string());
        return 0;
    }

    auto fileSize = std::filesystem::file_size(shaderFile);
    std::vector<char> buffer(fileSize);
    file.read(std::data(buffer), fileSize);
    file.close();

    const GLuint shader = glCreateShader(type);
    const GLchar* const source = std::data(buffer);
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, std::data(infoLog));

        glDeleteShader(shader);

        LOG_ERROR("Failed to compile shader {0}: {1}", shaderFile.string(), std::data(infoLog));
        return 0;
    }

    return shader;
}
