#include "ForestScene.h"
#include "StructShaderSources.h"
#include "Translate.h"
#include "Rotate.h"
#include "Scale.h"
#include "PointLight.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "FlashLight.h"
#include "RandomMovement.h"
#include "Application.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

static inline float frand(float a, float b) {
    return a + (b - a) * (float(std::rand()) / float(RAND_MAX));
}

void ForestScene::init()
{
    auto cam = getCamera();
    auto& lights = getLights();
    lights.clear();

    Application* app = Application::getInstance();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    lights.push_back(std::make_shared<FlashLight>(cam.get()));

    auto phongShader = ShaderManager::getShader("phong");
    auto constantShader = ShaderManager::getShader("constant");
    auto lambShader = ShaderManager::getShader("lamb");

    auto shrekTexture = std::make_shared<Texture>("assets/shrek.png");
    auto fionaTexture = std::make_shared<Texture>("assets/fiona.png");
    auto toiledTexture = std::make_shared<Texture>("assets/toiled.jpg");
    auto grassTexture = std::make_shared<Texture>("assets/grass.png");

    auto shrekModel = ModelLoader::load("shrek.obj");
    auto fionaModel = ModelLoader::load("fiona.obj");
    auto toiledModel = ModelLoader::load("toiled.obj");
    auto textAuthorModel = ModelLoader::load("text_tok0030.obj");
    auto is4Model = ModelLoader::load("IS4.obj");
    auto tigerModel = ModelLoader::load("Tiger_I.obj");

    const int fireflyCount = 30;
    std::vector<std::shared_ptr<FireflyLight>> fireflyLights;

    auto fireflyMaterial = std::make_shared<Material>(
        glm::vec3(0.4f, 0.5f, 0.2f),
        glm::vec3(1.2f, 1.0f, 0.6f),
        glm::vec3(0.5f, 0.9f, 0.5f),
        64.0f
    );

    for (int i = 0; i < fireflyCount; i++) {
        glm::vec3 base = glm::vec3(
            frand(-25.0f, 25.0f),
            frand(-1.0f, 2.0f),
            frand(-25.0f, 25.0f)
        );

        auto firefly = std::make_shared<FireflyLight>(
            base,
            glm::vec3(0.9f, 0.8f, 0.5f),
            /*glm::vec3(
                frand(0.1f,0.9f),
                frand(0.1f, 0.9f),
                frand(0.1f, 0.9f)
            ),*/
            1.0f,
            .5f, .2f
        );

        lights.push_back(firefly);
        fireflyLights.push_back(firefly);

        auto sphereObj = std::make_shared<DrawableObject>(
            sphere, sizeof(sphere) / (6 * sizeof(float)), 6,
            constantShader, fireflyMaterial
        );

        auto compositeTransform = std::make_shared<CompositeTransform>();
        auto move = std::make_shared<RandomMovement>(base, 0.3f, 3.0f, firefly);
        compositeTransform->addTransform(move);
        compositeTransform->addTransform(std::make_shared<Scale>(glm::vec3(0.03f)));

        sphereObj->getTransformations()->addTransform(compositeTransform);
        addObject(sphereObj);
    }

    if (shrekModel && shrekTexture) {
        auto shrekMaterial = std::make_shared<Material>(
            glm::vec3(0.2f, 0.25f, 0.1f),
            glm::vec3(0.6f, 0.7f, 0.4f),
            glm::vec3(0.01f, 0.01f, 0.01f),
            1.0f
        );

        auto shrekObj = std::make_shared<DrawableObject>(
            shrekModel, phongShader, shrekMaterial, shrekTexture
        );

        shrekObj->getTransformations()->addTransform(std::make_shared<Translate>(glm::vec3(8.0f, -1.8f, 5.0f)));
        shrekObj->getTransformations()->addTransform(std::make_shared<Scale>(glm::vec3(0.8f)));
        //shrekObj->getTransformations()->addTransform(std::make_shared<Rotate>(glm::radians(-45.0f), glm::vec3(0, 1, 0)));

        shrekObj->setId(getNextObjectId());

        addObject(shrekObj);
        std::cout << "Shrek loaded success" << std::endl;
    }

    if (fionaModel && fionaTexture) {
        auto fionaMaterial = std::make_shared<Material>(
            glm::vec3(0.25f, 0.2f, 0.15f),
            glm::vec3(0.8f, 0.6f, 0.5f),
            glm::vec3(0.4f, 0.3f, 0.2f),
            32.0f
        );

        auto fionaObj = std::make_shared<DrawableObject>(
            fionaModel, phongShader, fionaMaterial, fionaTexture
        );

        fionaObj->getTransformations()->addTransform(std::make_shared<Translate>(glm::vec3(8.0f, -1.8f, 7.0f)));
        fionaObj->getTransformations()->addTransform(std::make_shared<Scale>(glm::vec3(0.7f)));
        //fionaObj->getTransformations()->addTransform(std::make_shared<Rotate>(glm::radians(30.0f), glm::vec3(0, 1, 0)));

        fionaObj->setId(getNextObjectId());

        addObject(fionaObj);
        
        std::cout << "Fiona loaded success" << std::endl;
    }

    if (toiledModel && toiledTexture) {
        auto toiledMaterial = std::make_shared<Material>(
            glm::vec3(0.15f, 0.15f, 0.2f),
            glm::vec3(0.9f, 0.9f, 0.95f),
            glm::vec3(0.8f, 0.8f, 0.9f),
            128.0f
        );

        auto toiledObj = std::make_shared<DrawableObject>(
            toiledModel, phongShader, toiledMaterial, toiledTexture
        );

        toiledObj->getTransformations()->addTransform(std::make_shared<Translate>(glm::vec3(6.0f, -1.8f, 7.0f)));
        toiledObj->getTransformations()->addTransform(std::make_shared<Scale>(glm::vec3(0.5f)));
        toiledObj->getTransformations()->addTransform(std::make_shared<Rotate>(glm::radians(90.0f), glm::vec3(0, 1, 0)));

        addObject(toiledObj);
        std::cout << "Toilet loaded success" << std::endl;
    }

    if (textAuthorModel) {
        auto textAuthorMaterial = std::make_shared<Material>(
            glm::vec3(0.2f, 0.2f, 0.25f),
            glm::vec3(0.7f, 0.7f, 0.8f),
            glm::vec3(0.3f, 0.3f, 0.4f),
            16.0f
        );

        auto textAuthorObj = std::make_shared<DrawableObject>(
            textAuthorModel, phongShader, textAuthorMaterial
        );

        textAuthorObj->getTransformations()->addTransform(std::make_shared<Translate>(glm::vec3(0.0f, 0.0f, -2.0f)));
        textAuthorObj->getTransformations()->addTransform(std::make_shared<Scale>(glm::vec3(0.5f)));

        addObject(textAuthorObj);
        std::cout << "Text loaded success!" << std::endl;
    }

    if (is4Model) {
        auto is4Material = std::make_shared<Material>(
            glm::vec3(0.3f, 0.3f, 0.3f),
            glm::vec3(0.8f, 0.8f, 0.8f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            32.0f
        );

        auto is4Texture = std::make_shared<Texture>("assets/IS_4M.png");

        auto is4Object = std::make_shared<DrawableObject>(
            is4Model, phongShader, is4Material, is4Texture
        );

        is4Object->getTransformations()->addTransform(std::make_shared<Translate>(glm::vec3(0.0f, 0.0f, 0.0f)));
        is4Object->getTransformations()->addTransform(std::make_shared<Scale>(glm::vec3(1.0f)));

        addObject(is4Object);
        std::cout << "IS_4 tank loaded success!" << std::endl;
    }

    if (tigerModel) {
        auto tigerMaterial = std::make_shared<Material>(
            glm::vec3(0.2f, 0.15f, 0.1f),
            glm::vec3(0.7f, 0.6f, 0.4f),
            glm::vec3(0.3f, 0.3f, 0.3f),
            64.0f
        );

        auto tigerTexture = std::make_shared<Texture>("assets/PzVl_Tiger_I.png");

        auto tigerObject = std::make_shared<DrawableObject>(
            tigerModel, phongShader, tigerMaterial, tigerTexture
        );

        tigerObject->getTransformations()->addTransform(std::make_shared<Scale>(glm::vec3(1.f)));
        tigerObject->getTransformations()->addTransform(std::make_shared<Translate>(glm::vec3(10.f, .0f, 4.f)));

        addObject(tigerObject);
        std::cout << "Tiger tank loaded success!" << std::endl;
    }

    createForest();

    auto barkMaterial = std::make_shared<Material>(
        glm::vec3(0.02f, 0.02f, 0.015f),
        glm::vec3(0.10f, 0.07f, 0.05f),
        glm::vec3(0.02f, 0.02f, 0.015f),
        8.0f
    );

    auto bushMaterial = std::make_shared<Material>(
        glm::vec3(0.01f, 0.02f, 0.01f),
        glm::vec3(0.05f, 0.2f, 0.07f),
        glm::vec3(0.02f, 0.02f, 0.02f),
        4.0f
    );

    auto groundMaterial = std::make_shared<Material>(
        glm::vec3(0.01f, 0.01f, 0.015f),
        glm::vec3(0.06f, 0.09f, 0.07f),
        glm::vec3(0.02f, 0.02f, 0.02f),
        2.0f
    );

    for (const auto& t : forestTrees) {
        auto treeObj = std::make_shared<DrawableObject>(
            tree, sizeof(tree) / (6 * sizeof(float)), 6,
            phongShader, barkMaterial
        );

        treeObj->getTransformations()->addTransform(std::make_shared<Translate>(t.position));
        treeObj->getTransformations()->addTransform(std::make_shared<Rotate>(glm::radians(t.rotation), glm::vec3(0, 1, 0)));
        treeObj->getTransformations()->addTransform(std::make_shared<Scale>(glm::vec3(t.scale)));

        addObject(treeObj);
    }

    for (const auto& b : forestBushes) {
        auto bushObj = std::make_shared<DrawableObject>(
            bushes, sizeof(bushes) / (6 * sizeof(float)), 6,
            lambShader, bushMaterial
        );

        bushObj->getTransformations()->addTransform(std::make_shared<Translate>(b.position));
        bushObj->getTransformations()->addTransform(std::make_shared<Rotate>(glm::radians(b.rotation), glm::vec3(0, 1, 0)));
        bushObj->getTransformations()->addTransform(std::make_shared<Scale>(glm::vec3(b.scale)));

        addObject(bushObj);
    }

    auto ground = std::make_shared<DrawableObject>(
        plain,
        sizeof(plain) / (8 * sizeof(float)), 8,
        phongShader, groundMaterial, grassTexture
    );

    ground->getTransformations()->addTransform(std::make_shared<Translate>(glm::vec3(0.0f, -1.8f, 0.0f)));
    ground->getTransformations()->addTransform(std::make_shared<Scale>(glm::vec3(30.0f, 1.0f, 30.0f)));

    addObject(ground);

    std::cout << "ForestScene initialized!" << std::endl;
}

glm::vec3 ForestScene::generateRandomPosition()
{
    float x = ((float)std::rand() / RAND_MAX) * 40.0f - 20.0f;
    float z = ((float)std::rand() / RAND_MAX) * 40.0f - 20.0f;
    return glm::vec3(x, 0.0f, z);
}

void ForestScene::createForest() {
    forestTrees.clear();
    forestBushes.clear();

    for (int i = 0; i < 40; i++) {
        TreeData tree; tree.position = generateRandomPosition();
        tree.position.y = -1.8f;
        float r = (float)std::rand() / RAND_MAX; 
        tree.scale = 0.7f + r * 0.3f;
        tree.rotation = r * 360.0f;
        bool ok = true;
        for (auto& ex : forestTrees)
            if (glm::length(tree.position - ex.position) < 3.0f) {
                ok = false; 
                break;
            }
        if (ok) forestTrees.push_back(tree);
        else i--;
    }

    for (int i = 0; i < 150; i++) {
        TreeData bush; bush.position = generateRandomPosition();
        bush.position.y = -1.8f; 
        float r = (float)std::rand() / RAND_MAX;
        bush.scale = 0.2f + r * 0.15f;
        bush.rotation = r * 360.0f;
        bool ok = true;
        for (auto& ex : forestTrees)
            if (glm::length(bush.position - ex.position) < 2.0f) {
                ok = false; break;
            }
        if (ok) forestBushes.push_back(bush);
    }
}