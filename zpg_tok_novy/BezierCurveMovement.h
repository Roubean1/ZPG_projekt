#pragma once
#include "Transform.h"
#include "OpenGL_Include.h"
#include <glm/gtc/matrix_transform.hpp>

class BezierCurveMovement : public Transform
{
private:
    glm::vec3 p0, p1, p2, p3;
    float speed;
    mutable float startTime;
    mutable bool started;

public:
    BezierCurveMovement(const glm::vec3& point0, const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3, float movementSpeed = 1.0f);

    glm::mat4 getMatrix() const override;
};