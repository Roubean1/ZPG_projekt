#include "Camera.h"
#include <iostream>

Camera::Camera(const glm::vec3& eye, const glm::vec3& up)
    : eye(eye), up(up), alpha(0.0f), fi(0.0f)
{
    target = glm::vec3(0.0f, 0.0f, -1.0f);
    updateViewMatrix();
    updateProjectionMatrix();
}

void Camera::updateViewMatrix()
{
    viewMatrix = glm::lookAt(eye, eye + target, up);
}

void Camera::updateProjectionMatrix()
{
    projectionMatrix = glm::perspective(glm::radians(fov), screenAspectRatio, 0.1f, 100.0f);
}

glm::mat4 Camera::getViewMatrix()
{
    return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
    return projectionMatrix;
}

void Camera::setFov(float newFov)
{
    fov = glm::clamp(newFov, 10.0f, 90.0f);
    updateProjectionMatrix();
    Subject::notify(CameraO);
}

void Camera::updateScreenSize(int width, int height) {
    if (height == 0) height = 1;
    screenAspectRatio = static_cast<float>(width) / static_cast<float>(height);
    updateProjectionMatrix();
    Subject::notify(CameraO);
}

void Camera::updateOrientation(float deltaX, float deltaY)
{
    alpha += deltaX * mouseSensitivity;
    fi += deltaY * mouseSensitivity;

    if (fi > glm::radians(89.0f)) fi = glm::radians(89.0f);
    if (fi < glm::radians(-89.0f)) fi = glm::radians(-89.0f);

    target.x = cos(fi) * sin(alpha);
    target.y = sin(fi);
    target.z = -cos(fi) * cos(alpha);
    target = glm::normalize(target);

    updateViewMatrix();
    Subject::notify(CameraO);
}

void Camera::forward()
{
    eye += target * movementSpeed;
    updateViewMatrix();
    Subject::notify(CameraO);
}

void Camera::backward()
{
    eye -= target * movementSpeed;
    updateViewMatrix();
    Subject::notify(CameraO);
}

void Camera::left()
{
    glm::vec3 rightVec = glm::normalize(glm::cross(target, up));
    eye -= rightVec * movementSpeed;
    updateViewMatrix();
    Subject::notify(CameraO);
}

void Camera::right()
{
    glm::vec3 rightVec = glm::normalize(glm::cross(target, up));
    eye += rightVec * movementSpeed;
    updateViewMatrix();
    Subject::notify(CameraO);
}