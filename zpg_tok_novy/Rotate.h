#pragma once
#include "Transform.h"
#include "OpenGL_Include.h"

class Rotate : public Transform {
private:
    float angle;
    glm::vec3 axis;
public:
    Rotate(float angle, const glm::vec3& axis);
    glm::mat4 getMatrix() const override;
};