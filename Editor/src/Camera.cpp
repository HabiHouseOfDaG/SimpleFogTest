#include "Camera.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const f32 fov, const f32 aspectRatio, const f32 nearClip, const f32 farClip) :
    mFOV(fov), mAspectRatio(aspectRatio), mNearClip(nearClip), mFarClip(farClip),
    mProjection(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip))
{
}

void Camera::OnUpdate(GLFWwindow* const window, const f32 ts)
{
    const auto wKeyState = glfwGetKey(window, GLFW_KEY_W);
    if (wKeyState == GLFW_PRESS || wKeyState == GLFW_REPEAT)
        MoveForward();

    const auto sKeyState = glfwGetKey(window, GLFW_KEY_S);
    if (sKeyState == GLFW_PRESS || sKeyState == GLFW_REPEAT)
        MoveBackward();

    const auto aKeyState = glfwGetKey(window, GLFW_KEY_A);
    if (aKeyState == GLFW_PRESS || aKeyState == GLFW_REPEAT)
        RotateLeft();

    const auto dKeyState = glfwGetKey(window, GLFW_KEY_D);
    if (dKeyState == GLFW_PRESS || dKeyState == GLFW_REPEAT)
        RotateRight();
}

void Camera::SetViewportSize(const f32 width, const f32 height)
{
    mViewportWidth = width;
    mViewportHeight = height;
    UpdateProjection();
}

void Camera::UpdateProjection()
{
    mAspectRatio = mViewportWidth / mViewportHeight;
    mProjection = glm::perspective(glm::radians(mFOV), mAspectRatio, mNearClip, mFarClip);
}

void Camera::UpdateView()
{
    mView = glm::inverse(mTransform);
}

void Camera::MoveForward()
{
    mTransform = mTransform * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f) * MOVE_SPEED);
    UpdateView();
}

void Camera::MoveBackward()
{
    mTransform = mTransform * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f) * MOVE_SPEED);
    UpdateView();
}

void Camera::RotateLeft()
{
    mTransform = mTransform * glm::rotate(glm::mat4(1.0f), RotationSpeed(), glm::vec3(0.0f, 1.0f, 0.0f));
    UpdateView();
}

void Camera::RotateRight()
{
    mTransform = mTransform * glm::rotate(glm::mat4(1.0f), -RotationSpeed(), glm::vec3(0.0f, 1.0f, 0.0f));
    UpdateView();
}
