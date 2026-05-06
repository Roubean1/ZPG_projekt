#pragma once
#include "Scene.h"
#include <random>

class ForestScene : public Scene {
private:
    std::mt19937 rng;
    std::uniform_real_distribution<float> dist;

    struct TreeData {
        glm::vec3 position;
        float scale;
        float rotation;
    };

    std::vector<TreeData> forestTrees;
    std::vector<TreeData> forestBushes;

public:
    ForestScene(std::shared_ptr<Camera> cam)
        : Scene(cam), rng(std::random_device()()), dist(-50.0f, 50.0f) {
    }

    void init() override;

private:
    void createForest();
    glm::vec3 generateRandomPosition();
};
