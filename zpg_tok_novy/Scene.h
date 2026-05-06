#pragma once
#include <memory>
#include <vector>
#include "Camera.h"
#include "Light.h"
#include "DrawableObject.h"
#include "FlashLight.h"
#include "ModelLoader.h"
#include "ShaderManager.h"

#include "Models/tree.h"
#include "Models/gift.h"
#include "Models/sphere.h"
#include "Models/bushes.h"
#include "Models/plain.h"

class Scene {
protected:
    std::shared_ptr<Camera> camera;
    std::vector<std::shared_ptr<Light>> lights;
    std::vector<std::shared_ptr<DrawableObject>> objects;
    unsigned int nextObjectId = 1;

public:
    Scene(std::shared_ptr<Camera> cam)
        : camera(cam) {
    }

    virtual ~Scene() = default;

    virtual void init() = 0;

    virtual void draw();

    void addObject(std::shared_ptr<DrawableObject> obj) { objects.push_back(obj); }
    std::vector<std::shared_ptr<DrawableObject>>& getObjects() { return objects; }

    std::shared_ptr<Camera> getCamera() const { return camera; }

    std::vector<std::shared_ptr<Light>>& getLights() { return lights; }

    unsigned int getNextObjectId() { return nextObjectId++; }
    void setNextObjectId(unsigned int id) { nextObjectId = id; }
};