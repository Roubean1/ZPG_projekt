#include "FireflyLight.h"
#include "Action.h"

FireflyLight::FireflyLight(const glm::vec3& position,
    const glm::vec3& color,
    float constant,
    float linear,
    float quadratic)
    : PointLight(position, color, constant, linear, quadratic)
{
    notify(ActionNotify::LightO);
}

void FireflyLight::onNotify(ActionNotify eventType) {
    if (eventType == ActionNotify::CameraO || eventType == ActionNotify::LightO) {
        notify(ActionNotify::LightO);
    }
}

void FireflyLight::setPosition(const glm::vec3& newPos) {
    PointLight::setPosition(newPos);
    notify(ActionNotify::LightO);
}
