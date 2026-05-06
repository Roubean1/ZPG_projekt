#pragma once
#include "Scene.h"
#include "PointLight.h"
#include "ModelLoader.h"
#include "Texture.h"
#include "Camera.h"
#include <memory>

class SolarSystemScene : public Scene {
private:
    std::shared_ptr<PointLight> sunLight;
    std::shared_ptr<ModelLoader> planetModel;
	std::shared_ptr<ModelLoader> textModel;

    std::shared_ptr<Texture> sunTexture;
    std::shared_ptr<Texture> mercuryTexture;
    std::shared_ptr<Texture> venusTexture;
    std::shared_ptr<Texture> earthTexture;
    std::shared_ptr<Texture> moonTexture;
    std::shared_ptr<Texture> marsTexture;
    std::shared_ptr<Texture> jupiterTexture;
    std::shared_ptr<Texture> saturnTexture;
    std::shared_ptr<Texture> uranusTexture;
    std::shared_ptr<Texture> neptuneTexture;

    float timeScale;
    float orbitSpeedMultiplier;
    float rotationSpeedMultiplier;

public:
    SolarSystemScene(std::shared_ptr<Camera> cam);

    void init() override;
    void draw() override { Scene::draw(); }

    void setTimeScale(float scale) { timeScale = scale; }
    void setOrbitSpeedMultiplier(float multiplier) { orbitSpeedMultiplier = multiplier; }
    void setRotationSpeedMultiplier(float multiplier) { rotationSpeedMultiplier = multiplier; }
    float getTimeScale() const { return timeScale; }
};