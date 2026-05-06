#pragma once
#include "Transform.h"
#include "OpenGL_Include.h"

class CompositeTransform : public Transform {
private:
    std::vector<std::shared_ptr<Transform>> transforms;
public:
    void addTransform(std::shared_ptr<Transform> transform);
    glm::mat4 getMatrix() const override;
    //void clear();
};