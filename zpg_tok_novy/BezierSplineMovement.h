#pragma once
#include "Transform.h"
#include "OpenGL_Include.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

class BezierSplineMovement : public Transform
{
private:
    std::vector<glm::vec3> controlPoints;
    float speed;
    mutable float startTime;
    mutable bool started;
    bool loop;
    bool autoRotate;

public:
    BezierSplineMovement(const std::vector<glm::vec3>& points,
        float movementSpeed = 1.0f,
        bool shouldLoop = true,
        bool shouldAutoRotate = true);

    void addControlPoint(const glm::vec3& point);
    void clearControlPoints();
    const std::vector<glm::vec3>& getControlPoints() const { return controlPoints; }
    void setAutoRotate(bool rotate) { autoRotate = rotate; }

    glm::mat4 getMatrix() const override;

private:
    glm::vec3 calculateBezierPoint(float t, const glm::vec3& p0, const glm::vec3& p1,const glm::vec3& p2, const glm::vec3& p3) const;

    glm::vec3 calculateBezierTangent(float t, const glm::vec3& p0, const glm::vec3& p1,const glm::vec3& p2, const glm::vec3& p3) const;

    glm::mat4 calculateRotationMatrix(const glm::vec3& tangent) const;

    void getCurrentSegmentAndTime(float& normalizedTime, int& currentSegment, float& segmentTime) const;
};