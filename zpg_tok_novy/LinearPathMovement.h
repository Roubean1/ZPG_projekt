#pragma once
#include "Transform.h"
#include "OpenGL_Include.h"
#include <vector>
#include <cmath>

class LinearPathMovement : public Transform {
private:
    std::vector<glm::vec3> pathPoints;
    std::vector<float> segmentLengths;
    float totalLength;
    float speed;
    mutable float startTime;
    mutable bool started;

public:
    LinearPathMovement(const std::vector<glm::vec3>& points, float movementSpeed = 1.0f);

    glm::mat4 getMatrix() const override;
    bool isComplete() const;
    float getProgress() const;
};