#include "Translate.h"

Translate::Translate(const glm::vec3& translation) : translation(translation) {}

glm::mat4 Translate::getMatrix() const {
    return glm::translate(glm::mat4(1.0f), translation);
}