#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
private:
    glm::vec3 direction;

public:
    DirectionalLight(const glm::vec3& direction, const glm::vec3& color);

    glm::vec3 getPosition() const override;
    glm::vec3 getDirection() const override;
};
