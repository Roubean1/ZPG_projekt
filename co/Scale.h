#pragma once
#include "Transform.h"
#include "OpenGL_Include.h"

class Scale : public Transform {
private:
    glm::vec3 scale;
public:
    Scale(const glm::vec3& scale);
    glm::mat4 getMatrix() const override;
};