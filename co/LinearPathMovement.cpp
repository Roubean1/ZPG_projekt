#include "LinearPathMovement.h"
#include <GLFW/glfw3.h>

LinearPathMovement::LinearPathMovement(const std::vector<glm::vec3>& points, float movementSpeed) : pathPoints(points), speed(movementSpeed), startTime(0.0f), started(false) {

    segmentLengths.clear();
    totalLength = 0.0f;

    for (size_t i = 0; i < pathPoints.size() - 1; i++) {
        float length = glm::length(pathPoints[i + 1] - pathPoints[i]);
        segmentLengths.push_back(length);
        totalLength += length;
    }
}

glm::mat4 LinearPathMovement::getMatrix() const {
    if (pathPoints.empty()) return glm::mat4(1.0f);
    if (pathPoints.size() == 1) return glm::translate(glm::mat4(1.0f), pathPoints[0]);

    if (!started) {
        startTime = static_cast<float>(glfwGetTime());
        started = true;
    }

    float currentTime = static_cast<float>(glfwGetTime());
    float elapsed = currentTime - startTime;
    float distance = elapsed * speed;

    if (distance >= totalLength) {
        return glm::translate(glm::mat4(1.0f), pathPoints.back());
    }

    float accumulated = 0.0f;
    for (size_t i = 0; i < segmentLengths.size(); i++) {
        if (distance <= accumulated + segmentLengths[i]) {
            float segmentProgress = (distance - accumulated) / segmentLengths[i];
            glm::vec3 position = pathPoints[i] + segmentProgress * (pathPoints[i + 1] - pathPoints[i]);
            return glm::translate(glm::mat4(1.0f), position);
        }
        accumulated += segmentLengths[i];
    }

    return glm::translate(glm::mat4(1.0f), pathPoints.back());
}

bool LinearPathMovement::isComplete() const {
    if (!started) return false;
    if (pathPoints.empty()) return true;

    float currentTime = static_cast<float>(glfwGetTime());
    float elapsed = currentTime - startTime;
    return (elapsed * speed) >= totalLength;
}

float LinearPathMovement::getProgress() const {
    if (!started || totalLength == 0.0f) return 0.0f;

    float currentTime = static_cast<float>(glfwGetTime());
    float elapsed = currentTime - startTime;
    float distance = elapsed * speed;

    return std::min(distance / totalLength, 1.0f);
}