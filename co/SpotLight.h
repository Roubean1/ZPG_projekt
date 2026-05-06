#pragma once
#include "Light.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SpotLight : public Light
{
protected:
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

public:
    SpotLight(const glm::vec3& position,
        const glm::vec3& direction,
        const glm::vec3& color,
        float cutDeg = 12.5f,
        float outerDeg = 17.5f);

    glm::vec3 getPosition() const override;
    glm::vec3 getDirection() const override;

    float getCutOff() const override;
    float getOuterCutOff() const override;

    void setPosition(const glm::vec3& pos);
    void setDirection(const glm::vec3& dir);
};