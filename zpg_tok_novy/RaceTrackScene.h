#pragma once
#include "Scene.h"
#include "BezierSplineMovement.h"
#include "ModelLoader.h"
#include "Texture.h"
#include <memory>

class RaceTrackScene : public Scene {
private:
    std::shared_ptr<BezierSplineMovement> carSplineMovement;
    std::shared_ptr<DrawableObject> formulaCar;
    std::vector<glm::vec3> trackPoints;
    std::shared_ptr<Texture> formulaTexture;

public:
    RaceTrackScene(std::shared_ptr<Camera> cam);

    void init() override;
    void update();
    void draw() override;

    void createRaceTrack();
    void addTrackPoint(const glm::vec3& point);
    void startCarMovement();
    void drawTrackVisualization();
};