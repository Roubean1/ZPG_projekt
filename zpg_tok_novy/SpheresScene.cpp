#include "SpheresScene.h"
#include "StructShaderSources.h"
#include "Translate.h"
#include "CustomTransformation.h"
#include "Scale.h"
#include "Material.h"
#include "BezierCurveMovement.h"
#include "DynamicRotation.h"
#include <iostream>

void SpheresScene::init() {
    auto cam = getCamera();
    auto& lights = getLights();
    lights.clear();

    //lights.push_back(std::make_shared<AmbientLight>(glm::vec3(0.1f)));
    //lights.push_back(std::make_shared<DirectionalLight>(glm::vec3(0.4f), glm::normalize(glm::vec3(-0.5f, -1.0f, -0.3f))));
    lights.push_back(std::make_shared<PointLight>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.9f, 0.7f), 1.0f, 0.87f, 0.917f));
    //lights.push_back(std::make_shared<FlashLight>(cam.get()));
    float rotationSpeedMultiplier = 1;
    float timeScale = 1;
    const float mercuryRotationSpeed = 0.4f;

    auto getRotationSpeed = [&](float baseSpeed) { return baseSpeed * rotationSpeedMultiplier * timeScale; };

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
            76.0f),
        std::make_shared<Material>(
            glm::vec3(0.1f, 0.1f, 0.2f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            1.0f),
        std::make_shared<Material>(
            glm::vec3(0.1f, 0.2f, 0.1f),
            glm::vec3(0.2f, 0.6f, 0.3f),
            glm::vec3(0.6f, 0.9f, 0.6f),
            1.0f),
        std::make_shared<Material>(
            glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(0.7f, 0.7f, 0.2f),
            glm::vec3(0.1f, 0.1f, 0.1f),
            1.0f)
    };

    std::vector<std::shared_ptr<ShaderProgram>> shaders = {
        phongShader,
        phongShader,
        phongShader,
        phongShader
    };

    auto planetModel = ModelLoader::load("planet.obj");
    
    auto earthTexture = std::make_shared<Texture>("assets/textures/8k_earth.jpg");
    std::vector<std::shared_ptr<Texture>> texture = {
        nullptr,
        earthTexture,
        nullptr,
        nullptr
    };

    for (int i = 0; i < 4; i++) {
        auto sphereObj = std::make_shared<DrawableObject>(
            planetModel,
            shaders[i],
            materials[1],
            texture[i]
        );

        sphereObj->getTransformations()->addTransform(std::make_shared<Translate>(positions[i]));
        sphereObj->getTransformations()->addTransform(std::make_shared<Scale>(glm::vec3(0.5f)));
        sphereObj->getTransformations()->addTransform(std::make_shared<DynamicRotation>(glm::vec3(0, 1, 0), getRotationSpeed(mercuryRotationSpeed)));

        //sphereObj->getTransformations()

        addObject(sphereObj);
    };
    /*
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

    auto bezierMovement = std::make_shared<BezierCurveMovement>(
        glm::vec3(-2.0f, 0.0f, 0.0f),  // P0 - počáteční bod
        glm::vec3(-1.0f, 2.0f, 0.0f),  // P1 - první kontrolní bod
        glm::vec3(1.0f, 2.0f, 0.0f),   // P2 - druhý kontrolní bod
        glm::vec3(2.0f, 0.0f, 0.0f),   // P3 - koncový bod
        0.5f                            // rychlost pohybu
    );

    auto movingSphere = std::make_shared<DrawableObject>(
        sphere, sizeof(sphere) / (6 * sizeof(float)), 6,
        constantShader, testMaterial
    );

    movingSphere->getTransformations()->addTransform(bezierMovement);
    movingSphere->getTransformations()->addTransform(std::make_shared<Scale>(glm::vec3(0.3f)));

    addObject(movingSphere);

    */
    std::cout << "SpheresScene init!" << std::endl;
}

void SpheresScene::draw() {
    Scene::draw();
}