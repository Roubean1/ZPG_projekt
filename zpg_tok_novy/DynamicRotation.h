#pragma once
#include "Transform.h"
#include "OpenGL_Include.h"
#include <glm/gtc/matrix_transform.hpp>

class DynamicRotation : public Transform
{
private:
    glm::vec3 axis;
    float speed;
    mutable float angle;

public:
    DynamicRotation(const glm::vec3& axis, float speed = 1.0f);

    glm::mat4 getMatrix() const override;
};
