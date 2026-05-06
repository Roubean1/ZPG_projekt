#pragma once
#include "Light.h"

class AmbientLight : public Light
{
public:
    AmbientLight(const glm::vec3& color);

    glm::vec3 getPosition() const override;
    glm::vec3 getDirection() const override;
};
