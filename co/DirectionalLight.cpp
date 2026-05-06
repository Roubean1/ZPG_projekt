#include "DirectionalLight.h"
#include <glm/gtc/constants.hpp>

DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& color)
    : Light(LightType::DIRECTIONAL, color),
    direction(glm::normalize(direction))
{
}

glm::vec3 DirectionalLight::getPosition() const { return glm::vec3(0.0f); }
glm::vec3 DirectionalLight::getDirection() const { return direction; }
