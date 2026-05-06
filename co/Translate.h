#pragma once
#include "Transform.h"
#include "OpenGL_Include.h"

class Translate : public Transform {
private:
    glm::vec3 translation;
public:
    Translate(const glm::vec3& translation);
    glm::mat4 getMatrix() const override;
};