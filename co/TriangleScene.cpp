#include "TriangleScene.h"
#include "StructShaderSources.h"
#include "Rotate.h"
#include "DynamicRotation.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "Material.h"
#include <iostream>

void TriangleScene::init() {
    float trianglePoints[] = {
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
         0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
    };

    auto& lights = getLights();
    lights.clear();

    lights.push_back(std::make_shared<DirectionalLight>(
        glm::vec3(0.8f, 0.8f, 0.8f),
        glm::vec3(-1.0f, -1.0f, -1.0f)));

    auto constantShader = ShaderManager::getShader("constant");

    auto triMaterial = std::make_shared<Material>(
        glm::vec3(0.3f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.2f, 0.2f),
        glm::vec3(1.0f, 0.5f, 0.5f),
        32.0f
    );

    auto triangleObj = std::make_shared<DrawableObject>(
        trianglePoints,
        sizeof(trianglePoints) / (6 * sizeof(float)),
        6,
        constantShader,
        triMaterial
    );

    triangleObj->getTransformations()->addTransform(std::make_shared<DynamicRotation>(
        glm::vec3(0.0f, 1.0f, 0.0f), 1.0f));

    addObject(triangleObj);

    std::cout << "TriangleScene initialized!" << std::endl;
}

void TriangleScene::draw() {
    Scene::draw();
}