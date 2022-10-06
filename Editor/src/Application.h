#pragma once

#include "Core.h"

#include <string>
#include <vector>
#include <glm/glm.hpp>

struct GLFWwindow;
class Mesh;
class GLVertexArray;
class Shader;
class Camera;

class Application
{
public:
    Application() = default;
    ~Application();

    void Run();

private:
    bool Init();
    void Shutdown();

    void CreateScene();

    static void GlfwErrorCallback(int error, const char* description);

private:
    struct Cube
    {
        glm::mat4 transform{ 1.0 };
        glm::vec4 color{ 1.0f };

        Cube() = default;
        Cube(const glm::mat4& m, const glm::vec4& c) :
            transform(m), color(c) {}
    };

private:
    std::vector<Cube> mCubes;
    Ref<GLVertexArray> mVA;
    Ref<Shader> mShader;

    Ref<Camera> mCamera;

    GLFWwindow* mWindow = nullptr;
    bool mInitialized = false;
};
