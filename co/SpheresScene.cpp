#include "SpheresScene.h"
#include "StructShaderSources.h"
#include "Translate.h"
#include "CustomTransformation.h"
#include "Scale.h"
#include "Material.h"
#include <iostream>

void SpheresScene::init() {
    auto cam = getCamera();
    auto& lights = getLights();
    lights.clear();

    lights.push_back(std::make_shared<AmbientLight>(glm::vec3(0.1f)));
    lights.push_back(std::make_shared<DirectionalLight>(glm::vec3(0.4f), glm::normalize(glm::vec3(-0.5f, -1.0f, -0.3f))));
    lights.push_back(std::make_shared<PointLight>(glm::vec3(0.0f, 0.5f, 2.0f), glm::vec3(1.0f, 0.9f, 0.7f), 1.0f, 0.07f, 0.017f));
    lights.push_back(std::make_shared<FlashLight>(cam.get()));

    auto constantShader = ShaderManager::getShader("constant");
    auto phongShader = ShaderManager::getShader("phong");
    auto blinnShader = ShaderManager::getShader("blinn");
    auto lambShader = ShaderManager::getShader("lamb");

    std::vector<glm::vec3> positions = {
        glm::vec3(1.f, 0.0f, 0.0f),
        glm::vec3(-1.f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.f, 0.0f),
        glm::vec3(0.0f, -1.f, 0.0f)
    };

    std::vector<std::shared_ptr<Material>> materials = {
        std::make_shared<Material>(
            glm::vec3(0.6f, 0.2f, 0.2f),
            glm::vec3(0.8f, 0.3f, 0.3f),
            glm::vec3(0.2f, 0.2f, 0.2f),
            8.0f),
        std::make_shared<Material>(
            glm::vec3(0.1f, 0.1f, 0.2f),
            glm::vec3(0.3f, 0.3f, 0.8f),
            glm::vec3(0.8f, 0.8f, 1.0f),
            64.0f),
        std::make_shared<Material>(
            glm::vec3(0.1f, 0.2f, 0.1f),
            glm::vec3(0.2f, 0.6f, 0.3f),
            glm::vec3(0.6f, 0.9f, 0.6f),
            32.0f),
        std::make_shared<Material>(
            glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(0.7f, 0.7f, 0.2f),
            glm::vec3(0.1f, 0.1f, 0.1f),
            4.0f)
    };

    std::vector<std::shared_ptr<ShaderProgram>> shaders = {
        constantShader,
        phongShader,
        blinnShader,
        lambShader
    };

    for (int i = 0; i < 4; i++) {
        auto sphereObj = std::make_shared<DrawableObject>(
            sphere,
            sizeof(sphere) / (6 * sizeof(float)), 6,
            shaders[i],
            materials[i]
        );

        sphereObj->getTransformations()->addTransform(std::make_shared<Translate>(positions[i]));
        sphereObj->getTransformations()->addTransform(std::make_shared<Scale>(glm::vec3(0.5f)));

        addObject(sphereObj);
    }

    auto testMaterial = std::make_shared<Material>(
        glm::vec3(0.9f, 0.9f, 0.9f),
        glm::vec3(0.8f, 0.8f, 0.8f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        32.0f
    );

    auto customTransformMaterial = std::make_shared<Material>(
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.5f, 0.5f),
        32.0f
    );

    auto customSphere = std::make_shared<DrawableObject>(
        sphere, sizeof(sphere) / (6 * sizeof(float)), 6,
        constantShader, customTransformMaterial
    );

    customSphere->getTransformations()->addTransform(std::make_shared<Translate>(glm::vec3(1.0f, 1.0f, 0.0f)));
    customSphere->getTransformations()->addTransform(std::make_shared<Scale>(glm::vec3(10.3f)));
    customSphere->getTransformations()->addTransform(std::make_shared<CustomTransformation>());

    addObject(customSphere);

    for (int x = 0; x < 3; x++) {
        for (int z = 0; z < 3; z++) {
            auto testSphere = std::make_shared<DrawableObject>(
                sphere, sizeof(sphere) / (6 * sizeof(float)), 6,
                constantShader, testMaterial
            );

            float posX = (x - 1) * 2.0f;
            float posZ = (z - 1) * 2.0f;

            testSphere->getTransformations()->addTransform(std::make_shared<Translate>(glm::vec3(posX, 0.0f, posZ)));
            testSphere->getTransformations()->addTransform(std::make_shared<Scale>(glm::vec3(0.3f)));

            testSphere->setId(100 + x * 3 + z);

            addObject(testSphere);

        }
    }
    std::cout << "SpheresScene init!" << std::endl;
}

void SpheresScene::draw() {
    Scene::draw();
}