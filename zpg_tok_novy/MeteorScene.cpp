#include "MeteorScene.h"
#include "ShaderManager.h"
#include "ModelLoader.h"
#include "Translate.h"
#include "Scale.h"
#include "Rotate.h"
#include <iostream>
#include <cmath>

MeteorScene::MeteorScene(std::shared_ptr<Camera> cam) : Scene(cam), score(0), gameTime(0.0f), gameActive(true),
    lastSpawnTime(0.0f), spawnInterval(1.5f),
    rng(std::random_device()()), dist(-15.0f, 15.0f) {
}

void MeteorScene::init() {
    auto& lights = getLights();
    lights.clear();

    lights.push_back(std::make_shared<AmbientLight>(glm::vec3(0.3f, 0.3f, 0.3f)));
    lights.push_back(std::make_shared<DirectionalLight>(
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(0.8f, 0.8f, 0.8f)
    ));
    lights.push_back(std::make_shared<PointLight>(
        glm::vec3(0.0f, 10.0f, 0.0f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        1.0f, 0.09f, 0.032f
    ));

    auto phongShader = ShaderManager::getShader("phong");

    for (int i = 0; i < 3; i++) {
        spawnMeteor();
    }

    lastSpawnTime = getCurrentTime();
    std::cout << "Meteor Chase initialized!" << std::endl;
}

void MeteorScene::update() {
    if (!gameActive) return;

    float curTime = getCurrentTime();
    gameTime = curTime;

    if (curTime - lastSpawnTime >= spawnInterval) {
        spawnMeteor();
        lastSpawnTime = curTime;
        spawnInterval = std::max(0.5f, spawnInterval);
    }

    for (auto iterMeteor = activeMeteors.begin(); iterMeteor != activeMeteors.end();) {
        auto meteor = *iterMeteor;

        if (meteor->shouldRemove()) {

            auto& sceneObjects = getObjects();
            for (auto iterObject = sceneObjects.begin(); iterObject != sceneObjects.end();) {
                if ((*iterObject)->getId() == meteor->getId()) {
                    iterObject = sceneObjects.erase(iterObject);
                }
                else {
                    ++iterObject;
                }
            }

            iterMeteor = activeMeteors.erase(iterMeteor);
        }
        else {
            ++iterMeteor;
        }
    }
}

void MeteorScene::spawnMeteor() {
    MeteorType type = getRandomMeteorType();
    std::vector<glm::vec3> path = generateRandomPath();

    std::shared_ptr<Material> material;

    switch (type) {
    case MeteorType::SMALL:
        material = std::make_shared<Material>(
            glm::vec3(0.3f, 0.3f, 0.3f),
            glm::vec3(0.9f, 0.9f, 0.9f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            32.0f
        );
        break;
    case MeteorType::LARGE:
        material = std::make_shared<Material>(
            glm::vec3(0.4f, 0.4f, 0.1f),
            glm::vec3(1.0f, 1.0f, 0.6f),
            glm::vec3(0.6f, 0.6f, 0.3f),
            64.0f
        );
        break;
    case MeteorType::DANGEROUS:
        material = std::make_shared<Material>(
            glm::vec3(0.4f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.3f, 0.3f),
            glm::vec3(0.9f, 0.2f, 0.2f),
            128.0f
        );
        break;
    case MeteorType::BONUS:
        material = std::make_shared<Material>(
            glm::vec3(0.0f, 0.3f, 0.0f),
            glm::vec3(0.3f, 1.0f, 0.3f),
            glm::vec3(0.2f, 0.9f, 0.2f),
            256.0f
        );
        break;
    }

    auto shader = ShaderManager::getShader("phong");
    float lifetime = 15.0f + (static_cast<float>(rand()) / RAND_MAX) * 10.0f;

    auto meteorObj = std::make_shared<Meteor>(nullptr, shader, material, type, path, lifetime);

    auto meteorVisual = std::make_shared<DrawableObject>(
        sphere, sizeof(sphere) / (6 * sizeof(float)), 6, shader, material
    );

    float speed = 1.0f + (static_cast<float>(rand()) / RAND_MAX) * 2.0f;
    auto pathMovement = std::make_shared<LinearPathMovement>(path, speed);

    auto compositeTransform = std::make_shared<CompositeTransform>();
    compositeTransform->addTransform(pathMovement);

    float scale = 0.3f;
    if (type == MeteorType::LARGE) scale = 0.5f;
    else if (type == MeteorType::SMALL) scale = 0.2f;

    compositeTransform->addTransform(std::make_shared<Scale>(glm::vec3(scale)));
    compositeTransform->addTransform(
        std::make_shared<Rotate>(glm::radians(static_cast<float>(rand() % 360)), glm::vec3(0, 1, 0))
    );

    meteorVisual->getTransformations()->addTransform(compositeTransform);

    unsigned int meteorId = getNextObjectId();
    meteorVisual->setId(meteorId);
    meteorObj->setId(meteorId);

    addObject(meteorVisual);
    activeMeteors.push_back(meteorObj);
}

std::vector<glm::vec3> MeteorScene::generateRandomPath() {
    std::vector<glm::vec3> path;
    int numPoints = 3 + rand() % 3;

    for (int i = 0; i < numPoints; i++) {
        float x = dist(rng);
        float y = 2.0f + (static_cast<float>(rand()) / RAND_MAX) * 3.0f;
        float z = -10.0f - (static_cast<float>(rand()) / RAND_MAX) * 10.0f;
        path.push_back(glm::vec3(x, y, z));
    }

    return path;
}

MeteorType MeteorScene::getRandomMeteorType() {
    int random = rand() % 100;
    if (random < 40) return MeteorType::SMALL;
    if (random < 70) return MeteorType::LARGE;
    if (random < 85) return MeteorType::DANGEROUS;
    return MeteorType::BONUS;
}

void MeteorScene::onMeteorHit(std::shared_ptr<Meteor> meteor) {
    if (!meteor->getIsActive()) return;

    int points = meteor->getPoints();
    score += points;
    meteor->deactivate();

    std::cout << "Hit: " << points << " | Score: " << score << std::endl;

    auto& sceneObjects = getObjects();
    for (auto iterObject = sceneObjects.begin(); iterObject != sceneObjects.end(); ++iterObject) {
        if ((*iterObject)->getId() == meteor->getId()) {
            sceneObjects.erase(iterObject);
            break;
        }
    }

    auto iterMeteor = std::find(activeMeteors.begin(), activeMeteors.end(), meteor);
    if (iterMeteor != activeMeteors.end()) {
        activeMeteors.erase(iterMeteor);
    }
}

void MeteorScene::draw() {
    Scene::draw();
}

float MeteorScene::getCurrentTime() const {
    return static_cast<float>(glfwGetTime());
}
