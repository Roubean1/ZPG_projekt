#pragma once
#include "Light.h"

class PointLight : public Light
{
private:
    glm::vec3 position;
    float constant, linear, quadratic;

public:
    PointLight(const glm::vec3& position,
        const glm::vec3& color,
        float constant = 1.0f,
        float linear = 0.09f,
        float quadratic = 0.032f);

    glm::vec3 getPosition() const override;
    glm::vec3 getDirection() const override;

    float getConstant() const override;
    float getLinear() const override;
    float getQuadratic() const override;

    void setPosition(const glm::vec3& newPos) {
        position = newPos;
        notify(ActionNotify::LightO);
    }
};