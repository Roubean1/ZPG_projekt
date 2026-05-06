#pragma once
#include "Scene.h"

class TriangleScene : public Scene {
private:
    float rotationAngle = 0.0f;

public:
    TriangleScene(std::shared_ptr<Camera> cam)
        : Scene(cam) {
    }

    void init() override;
    void draw() override;
};
