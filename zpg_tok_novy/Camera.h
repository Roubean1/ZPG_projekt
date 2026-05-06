#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Observer.h"
#include "Subject.h"
#include "Action.h"

class Camera : public Subject
{
private:
    float alpha;
    float fi;

    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 up;

    float mouseSensitivity = 0.002f;
    float movementSpeed = 0.1f;
    float fov = 45.0f;
    float screenAspectRatio = 4.0f / 3.0f;

    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projectionMatrix = glm::mat4(1.0f);

    void updateViewMatrix();
    void updateProjectionMatrix();

public:
    Camera(const glm::vec3& eye, const glm::vec3& up);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    glm::vec3 getPosition() const { return eye; }
    glm::vec3 getTarget() const { return target; }


    void setFov(float newFov);
    void updateScreenSize(int width, int height);

    void updateOrientation(float deltaX, float deltaY);

    void forward();
    void backward();
    void left();
    void right();

    void setPosition(const glm::vec3& newPosition) {
        eye = newPosition;
        updateViewMatrix();
    }

    void setTarget(const glm::vec3& newTarget) {
        target = glm::normalize(newTarget);
        updateViewMatrix();
    }
};