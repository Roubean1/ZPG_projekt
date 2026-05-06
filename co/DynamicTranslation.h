#pragma once
#include "Transform.h"
#include "OpenGL_Include.h"
#include <glm/gtc/matrix_transform.hpp>

class DynamicTranslation : public Transform
{
private:
    glm::vec3 direction;
    float speed;
    mutable float time;

public:
    DynamicTranslation(const glm::vec3& direction, float speed = 1.0f);

    glm::mat4 getMatrix() const override;
};
