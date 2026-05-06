#include "AmbientLight.h"

AmbientLight::AmbientLight(const glm::vec3& color)
    : Light(LightType::AMBIENT, color)
{
}

glm::vec3 AmbientLight::getPosition() const { return glm::vec3(0.0f); }
glm::vec3 AmbientLight::getDirection() const { return glm::vec3(0.0f); }
