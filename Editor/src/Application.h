#pragma once

#include "Core.h"

#include <string>

struct GLFWwindow;

class Application
{
public:
    Application() = default;
    ~Application();

    void Run();

private:
    bool Init();
    void Shutdown();

    static void GlfwErrorCallback(int error, const char* description);

private:
    GLFWwindow* mWindow = nullptr;
    bool mInitialized = false;
};
