#include "SpotLight.h"

SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction,const glm::vec3& color,float cutDeg,float outerDeg)
    : Light(LightType::SPOT, color),position(position),direction(glm::normalize(direction)),cutOff(glm::cos(glm::radians(cutDeg))),outerCutOff(glm::cos(glm::radians(outerDeg)))
{
}

glm::vec3 SpotLight::getPosition() const { return position; }
glm::vec3 SpotLight::getDirection() const { return direction; }

float SpotLight::getCutOff() const { return cutOff; }
float SpotLight::getOuterCutOff() const { return outerCutOff; }

void SpotLight::setPosition(const glm::vec3& pos)
{
    position = pos;
    notify(ActionNotify::LightO);
}

void SpotLight::setDirection(const glm::vec3& dir)
{
    direction = glm::normalize(dir);
    notify(ActionNotify::LightO);
}