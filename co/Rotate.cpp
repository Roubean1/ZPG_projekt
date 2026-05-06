#include "Rotate.h"

Rotate::Rotate(float angle, const glm::vec3& axis) : angle(angle), axis(axis) {}

glm::mat4 Rotate::getMatrix() const {
    return glm::rotate(glm::mat4(1.0f), angle, axis);
}