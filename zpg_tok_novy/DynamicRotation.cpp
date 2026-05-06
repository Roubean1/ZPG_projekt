#include "DynamicRotation.h"
#include <glm/gtc/constants.hpp>

DynamicRotation::DynamicRotation(const glm::vec3& axis, float speed)
    : axis(axis), speed(speed), angle(0.0f)
{
}

glm::mat4 DynamicRotation::getMatrix() const
{
    angle += speed * 0.016f;
    if (angle > glm::two_pi<float>()) angle -= glm::two_pi<float>();

    return glm::rotate(glm::mat4(1.0f), angle, axis);
}
