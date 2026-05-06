#pragma once
#include "Transform.h"
#include <glm/glm.hpp>

class CustomTransformation : public Transform
{
private:
    glm::mat4 customMat;
public:
    CustomTransformation();
    glm::mat4 getMatrix() const override;
};