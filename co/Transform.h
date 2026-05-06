#pragma once
#include "OpenGL_Include.h"

class Transform {
public:
    virtual ~Transform() = default;
    virtual glm::mat4 getMatrix() const = 0;
};