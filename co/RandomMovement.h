#pragma once
#include "Transform.h"
#include "FireflyLight.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <memory>

class RandomMovement : public Transform{
private:
    glm::vec3 origin;
    float speed;
    float range;
    float offsetX, offsetY, offsetZ;
    std::shared_ptr<FireflyLight> linkedLight;

public:
    RandomMovement(const glm::vec3& startPos, float speed, float range);
    RandomMovement(const glm::vec3& startPos, float speed, float range,
                   std::shared_ptr<FireflyLight> light);

    glm::mat4 getMatrix() const override;
    glm::vec3 getCurrentPosition() const;
};
