#pragma once

#include "Core.h"

#include <glm/glm.hpp>

struct GLFWwindow;

class Camera
{
public:
    Camera() = default;
    Camera(const f32 fov, const f32 aspectRatio, const f32 nearClip, const f32 farClip);

    void OnUpdate(GLFWwindow* const window, const f32 ts);

    void SetViewportSize(const f32 width, const f32 height);

    const glm::mat4& GetView() const { return mView; }
    const glm::mat4& GetProjection() const { return mProjection; }
    glm::mat4 GetViewProjection() const { return mProjection * mView; }

private:
    void UpdateProjection();
    void UpdateView();

    void MoveForward();
    void MoveBackward();
    void RotateLeft();
    void RotateRight();

    constexpr f32 RotationSpeed() const { return 0.05f; }

private:
    static constexpr f32 MOVE_SPEED = 0.25f;

private:
    f32 mFOV = 45.0f;
    f32 mAspectRatio = 1.778f;
    f32 mNearClip = 0.1f;
    f32 mFarClip = 1000.0f;

    glm::mat4 mTransform{ 1.0f };
    glm::mat4 mView{ 1.0f };
    glm::mat4 mProjection{ 1.0f };

    f32 mViewportWidth = 1280.0f;
    f32 mViewportHeight = 720.0f;
};
