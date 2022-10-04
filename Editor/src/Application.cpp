#include "Application.h"

#include "Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

Application::~Application()
{
    Shutdown();
}

void Application::Run()
{
    if (!Init())
    {
        LOG_ERROR("Failed to init application.");
        return;
    }

    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();

        glfwSwapBuffers(mWindow);
    }

    Shutdown();
}

bool Application::Init()
{
    glfwSetErrorCallback(GlfwErrorCallback);

    if (const auto result = glfwInit(); !result)
        return false;

    mWindow = glfwCreateWindow(1200, 900, "Simple Fog Editor", nullptr, nullptr);

    glfwMakeContextCurrent(mWindow);
    if (const auto result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); !result)
        return false;

    glfwSwapInterval(1);

    return true;
}

void Application::Shutdown()
{
    glfwTerminate();

    mWindow = nullptr;
}

void Application::GlfwErrorCallback(int error, const char* description)
{
    LOG_ERROR("GLFW Error ({0}): {1}", error, description);
}
