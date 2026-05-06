#include "PointLight.h"
#include "Action.h"

PointLight::PointLight(const glm::vec3& position,const glm::vec3& color,float constant,float linear,float quadratic)
    : Light(LightType::POINT, color),position(position),constant(constant),linear(linear),quadratic(quadratic)
{
}

glm::vec3 PointLight::getPosition() const { return position; }
glm::vec3 PointLight::getDirection() const { return glm::vec3(0.0f); }

float PointLight::getConstant() const { return constant; }
float PointLight::getLinear() const { return linear; }
float PointLight::getQuadratic() const { return quadratic; }