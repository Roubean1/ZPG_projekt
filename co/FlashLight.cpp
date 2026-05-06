#include "FlashLight.h"

FlashLight::FlashLight(Camera* cam): SpotLight(cam->getPosition(), cam->getTarget(), glm::vec3(1.0f), 12.5f, 20.5f),camera(cam)
{
    camera->addObserver(this);
}

void FlashLight::onNotify(ActionNotify eventType)
{
    if (eventType == ActionNotify::CameraO)
    {
        this->position = camera->getPosition();
        this->direction = camera->getTarget();
    }

    notify(ActionNotify::LightO);
}
