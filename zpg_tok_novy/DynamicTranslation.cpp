#include "DynamicTranslation.h"
#include <glm/gtc/constants.hpp>
#include <cmath>

DynamicTranslation::DynamicTranslation(const glm::vec3& direction, float speed)
    : direction(direction), speed(speed), time(0.0f)
{
}

glm::mat4 DynamicTranslation::getMatrix() const
{
    time += 0.016f;
    glm::vec3 offset = direction * std::sin(time * speed);
    return glm::translate(glm::mat4(1.0f), offset);
}
