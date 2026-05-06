#pragma once
#include "Scene.h"
#include "Light.h"
#include "Camera.h"
#include <vector>
#include <memory>

class SpheresScene : public Scene {
public:
    SpheresScene(std::shared_ptr<Camera> cam)
        : Scene(cam) {
    }

    void init() override;
    void draw() override;
};
