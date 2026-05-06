#include "RandomMovement.h"
#include <cstdlib>
#include <cmath>

RandomMovement::RandomMovement(const glm::vec3& startPos, float speed, float range)
    : origin(startPos), speed(speed), range(range), linkedLight(nullptr)
{
    offsetX = static_cast<float>(rand() % 1000) / 100.0f;
    offsetY = static_cast<float>(rand() % 1000) / 100.0f;
    offsetZ = static_cast<float>(rand() % 1000) / 100.0f;
}

RandomMovement::RandomMovement(const glm::vec3& startPos, float speed, float range,
    std::shared_ptr<FireflyLight> light)
    : origin(startPos), speed(speed), range(range), linkedLight(light)
{
    offsetX = static_cast<float>(rand() % 1000) / 100.0f;
    offsetY = static_cast<float>(rand() % 1000) / 100.0f;
    offsetZ = static_cast<float>(rand() % 1000) / 100.0f;
}
glm::mat4 RandomMovement::getMatrix() const {
    float t = static_cast<float>(glfwGetTime());

    float x = origin.x + std::sin(t * speed * 0.7f + offsetX) * range;
    float z = origin.z + std::sin(t * speed * 0.9f + offsetZ) * range;

    float y = origin.y + std::cos(t * speed * 1.3f + offsetY) * (range * 0.1f);

    glm::vec3 currentPos = glm::vec3(x, y, z);

    if (linkedLight) {
        linkedLight->setPosition(currentPos);
    }

    return glm::translate(glm::mat4(1.0f), currentPos);
}

glm::vec3 RandomMovement::getCurrentPosition() const {
    float t = static_cast<float>(glfwGetTime());
    return glm::vec3(
        origin.x + std::sin(t * speed * 0.7f + offsetX) * range,
        origin.y + std::cos(t * speed * 1.3f + offsetY) * (range * 0.1f),
        origin.z + std::sin(t * speed * 0.9f + offsetZ) * range
    );
}