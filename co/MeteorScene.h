#pragma once
#include "Scene.h"
#include "Meteor.h"
#include <random>
#include <chrono>

class MeteorScene : public Scene {
private:
    int score;
    float gameTime;
    bool gameActive;

    float lastSpawnTime;
    float spawnInterval;

    std::mt19937 rng;
    std::uniform_real_distribution<float> dist;

    std::vector<std::shared_ptr<Meteor>> activeMeteors;

public:
    MeteorScene(std::shared_ptr<Camera> cam);
    void init() override;
    void update();
    void draw() override;

    void spawnMeteor();
    void onMeteorHit(std::shared_ptr<Meteor> meteor);

    std::vector<glm::vec3> generateRandomPath();
    MeteorType getRandomMeteorType();

    void startGame() { gameActive = true; }
    void endGame() { gameActive = false; }

    const std::vector<std::shared_ptr<Meteor>>& getActiveMeteors() const { return activeMeteors; }

    float getCurrentTime() const;
    float getTimeSince(float startTime) const { return getCurrentTime() - startTime; }
};