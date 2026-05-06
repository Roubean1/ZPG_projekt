#pragma once
#include "PointLight.h"
#include "Observer.h"
#include <glm/vec3.hpp>

class FireflyLight : public PointLight, public Observer {
public:
    FireflyLight(const glm::vec3& position,
        const glm::vec3& color = glm::vec3(1.f, 1.0f, 0.6f),
        float constant = 1.0f,
        float linear = 0.35f,
        float quadratic = 0.44f);

    void onNotify(ActionNotify eventType) override;
    void setPosition(const glm::vec3& newPos);
};
