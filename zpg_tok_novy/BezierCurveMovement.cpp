#include "BezierCurveMovement.h"
#include <GLFW/glfw3.h>

BezierCurveMovement::BezierCurveMovement(const glm::vec3& point0, const glm::vec3& point1,
    const glm::vec3& point2, const glm::vec3& point3,float movementSpeed)
    : p0(point0), p1(point1), p2(point2), p3(point3), speed(movementSpeed), started(false)
{
}

glm::mat4 BezierCurveMovement::getMatrix() const
{
    if (!started) {
        startTime = static_cast<float>(glfwGetTime());
        started = true;
    }

    float currentTime = static_cast<float>(glfwGetTime());
    float elapsed = currentTime - startTime;

    float t = fmod(elapsed * speed, 1.0f);

    float u = 1.0f - t;
    float u2 = u * u;
    float t2 = t * t;
    float u3 = u2 * u;
    float t3 = t2 * t;

    glm::vec3 position = u3 * p0 + 3 * u2 * t * p1 + 3 * u * t2 * p2 + t3 * p3;

    return glm::translate(glm::mat4(1.0f), position);
}