#pragma once
#include <glm/vec3.hpp>

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    Material(const glm::vec3& amb = glm::vec3(0.1f),
        const glm::vec3& diff = glm::vec3(0.7f),
        const glm::vec3& spec = glm::vec3(0.3f),
        float shin = 32.0f)
        : ambient(amb), diffuse(diff), specular(spec), shininess(shin) {
    }
};