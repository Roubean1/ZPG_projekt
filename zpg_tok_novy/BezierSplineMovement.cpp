#include "BezierSplineMovement.h"
#include <iostream>

BezierSplineMovement::BezierSplineMovement(const std::vector<glm::vec3>& points,
    float movementSpeed, bool shouldLoop, bool shouldAutoRotate)
    : controlPoints(points), speed(movementSpeed), started(false),
    loop(shouldLoop), autoRotate(shouldAutoRotate)
{
}

void BezierSplineMovement::addControlPoint(const glm::vec3& point)
{
    controlPoints.push_back(point);
}

void BezierSplineMovement::clearControlPoints()
{
    controlPoints.clear();
    started = false;
}

glm::mat4 BezierSplineMovement::getMatrix() const
{
    if (controlPoints.size() < 4) {
        return glm::mat4(1.0f);
    }

    if (!started) {
        startTime = static_cast<float>(glfwGetTime());
        started = true;
    }

    float normalizedTime;
    int currentSegment;
    float segmentTime;
    getCurrentSegmentAndTime(normalizedTime, currentSegment, segmentTime);

    int baseIndex = currentSegment * 3;
    glm::vec3 p0 = controlPoints[baseIndex];
    glm::vec3 p1 = controlPoints[baseIndex + 1];
    glm::vec3 p2 = controlPoints[baseIndex + 2];
    glm::vec3 p3 = controlPoints[baseIndex + 3];

    glm::vec3 position = calculateBezierPoint(segmentTime, p0, p1, p2, p3);

    glm::mat4 transformation = glm::translate(glm::mat4(1.0f), position);

    if (autoRotate) {
        glm::vec3 tangent = calculateBezierTangent(segmentTime, p0, p1, p2, p3);
        glm::mat4 rotation = calculateRotationMatrix(tangent);
        transformation = transformation * rotation;
    }

    return transformation;
}

void BezierSplineMovement::getCurrentSegmentAndTime(float& normalizedTime, int& currentSegment, float& segmentTime) const
{
    float currentTime = static_cast<float>(glfwGetTime());
    float elapsed = currentTime - startTime;

    int segmentCount = (controlPoints.size() - 1) / 3;
    if (segmentCount < 1) {
        currentSegment = 0;
        segmentTime = 0.0f;
        return;
    }

    float totalTime = segmentCount / speed;

    normalizedTime = fmod(elapsed * speed, segmentCount);

    if (!loop && elapsed * speed >= segmentCount) {
        normalizedTime = static_cast<float>(segmentCount) - 0.0001f;
    }

    currentSegment = static_cast<int>(normalizedTime);
    segmentTime = normalizedTime - currentSegment;

    currentSegment = glm::clamp(currentSegment, 0, segmentCount - 1);
    segmentTime = glm::clamp(segmentTime, 0.0f, 1.0f);
}

glm::vec3 BezierSplineMovement::calculateBezierPoint(float t, const glm::vec3& p0,
    const glm::vec3& p1, const glm::vec3& p2,
    const glm::vec3& p3) const
{
    float u = 1.0f - t;
    float u2 = u * u;
    float t2 = t * t;
    float u3 = u2 * u;
    float t3 = t2 * t;

    return u3 * p0 + 3.0f * u2 * t * p1 + 3.0f * u * t2 * p2 + t3 * p3;
}

glm::vec3 BezierSplineMovement::calculateBezierTangent(float t, const glm::vec3& p0,
    const glm::vec3& p1, const glm::vec3& p2,
    const glm::vec3& p3) const
{
    float u = 1.0f - t;
    float u2 = u * u;
    float t2 = t * t;

    glm::vec3 tangent = 3.0f * u2 * (p1 - p0) +
        6.0f * u * t * (p2 - p1) +
        3.0f * t2 * (p3 - p2);

    if (glm::length(tangent) > 0.0001f) {
        return glm::normalize(tangent);
    }
    else {
        return glm::vec3(1.0f, 0.0f, 0.0f);
    }
}

glm::mat4 BezierSplineMovement::calculateRotationMatrix(const glm::vec3& tangent) const
{

    glm::vec3 forward = glm::vec3(1.0f, 0.0f, 0.0f);

    if (glm::length(tangent - forward) < 0.0001f) {
        return glm::mat4(1.0f);
    }

    glm::vec3 axis = glm::cross(forward, tangent);
    float axisLength = glm::length(axis);

    if (axisLength < 0.0001f) {
        if (glm::dot(forward, tangent) < 0.0f) {
            return glm::mat4(
                glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f),
                glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
                glm::vec4(0.0f, 0.0f, -1.0f, 0.0f),
                glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
            );
        }
        else {
            return glm::mat4(1.0f);
        }
    }

    axis = glm::normalize(axis);

    float angle = acos(glm::clamp(glm::dot(forward, tangent), -1.0f, 1.0f));

    float c = cos(angle);
    float s = sin(angle);
    float t2 = 1.0f - c;

    glm::vec3 n = axis;
    float nx = n.x, ny = n.y, nz = n.z;

    return glm::mat4(
        glm::vec4(t2 * nx * nx + c, t2 * nx * ny + s * nz, t2 * nx * nz - s * ny, 0.0f),
        glm::vec4(t2 * nx * ny - s * nz, t2 * ny * ny + c, t2 * ny * nz + s * nx, 0.0f),
        glm::vec4(t2 * nx * nz + s * ny, t2 * ny * nz - s * nx, t2 * nz * nz + c, 0.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );
}