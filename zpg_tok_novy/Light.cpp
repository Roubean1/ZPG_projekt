#include "Light.h"

Light::Light(LightType t, const glm::vec3& c)
    : type(t), color(c)
{
}

Light::~Light() = default;

LightType Light::getType() const { return type; }
glm::vec3 Light::getColor() const { return color; }

void Light::setColor(const glm::vec3& c) {
    color = c;
    notify(ActionNotify::LightO);
}