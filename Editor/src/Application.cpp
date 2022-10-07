#include "Application.h"

#include "Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "GLVertexArray.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Application::~Application()
{
    Shutdown();
}

void Application::Run()
{
    if (!Init())
    {
        LOG_CRITICAL("Failed to init application.");
        return;
    }

    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();

        mCamera->OnUpdate(mWindow, 0.0f);

        glClearColor(mFogColor.r, mFogColor.g, mFogColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        mVA->Bind();

        mShader->Bind();
        mShader->SetUniform("u_View", mCamera->GetView());
        mShader->SetUniform("u_Projection", mCamera->GetProjection());
        mShader->SetUniform("u_FogColor", mFogColor);
        mShader->SetUniform("u_FogIntensity", mFogIntensity);

        for (const auto& cube : mCubes)
        {
            mShader->SetUniform("u_Transform", cube.transform);
            mShader->SetUniform("u_Color", cube.color);

            mVA->Render();
        }

        mVA->Unbind();

        RenderFogAttrsWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(mWindow);
    }

    Shutdown();
}

bool Application::Init()
{
    assert(!mInitialized && "Application is already initialized!");

    glfwSetErrorCallback(GlfwErrorCallback);

    if (!glfwInit())
    {
        LOG_CRITICAL("Failed to initialize GLFW!");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(1280, 720, "Simple Fog Editor", nullptr, nullptr);

    glfwMakeContextCurrent(mWindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_CRITICAL("Failed to initialize glad GL loader!");
        return false;
    }

    glfwSwapInterval(1);

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL3_Init("#version 460 core");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    mInitialized = true;

    mVA = GLVertexArray::Create(Mesh::CreateCube());
    mShader = Shader::Create("assets/shaders/Fog.vert", "assets/shaders/Fog.frag");
    if (!mShader)
        return false;

    mCamera = CreateRef<Camera>(30.0f, 1.788f, 0.1f, 1000.0f);

    CreateScene();

    return true;
}

void Application::Shutdown()
{
    if (mInitialized)
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    glfwTerminate();

    mVA = nullptr;
    mWindow = nullptr;
    mInitialized = false;
}

void Application::CreateScene()
{
    mCubes = {
        Cube {
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)),
            glm::vec4 { 1.0f, 0.5f, 0.5f, 1.0f }
        },
        Cube {
            glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.0f, -5.0f)),
            glm::vec4 { 1.0f, 1.0f, 0.5f, 1.0f }
        },
        Cube {
            glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.0f, 0.0f)),
            glm::vec4 { 0.5f, 0.5f, 0.5f, 1.0f }
        },
        Cube {
            glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, -15.0f)),
            glm::vec4 { 1.0f, 1.0f, 0.0f, 1.0f }
        },
        Cube {
            glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, 15.0f)),
            glm::vec4 { 1.0f, 0.0f, 0.0f, 1.0f }
        }
    };
}

void Application::RenderFogAttrsWindow()
{
    ImGui::Begin("Fog Attributes");

    ImGui::ColorPicker3("Fog Color", glm::value_ptr(mFogColor));
    ImGui::DragFloat("Fog Intensity", &mFogIntensity, 0.01f, 0.0f, 1.0f);

    ImGui::End();
}

void Application::GlfwErrorCallback(int error, const char* description)
{
    LOG_ERROR("GLFW Error ({0}): {1}", error, description);
}
