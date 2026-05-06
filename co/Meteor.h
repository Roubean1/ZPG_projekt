#pragma once
#include "DrawableObject.h"
#include "LinearPathMovement.h"
#include "MeteorType.h"
#include <GLFW/glfw3.h>

class Meteor : public DrawableObject {
private:
    MeteorType type;
    int points;
    float spawnTime;
    float lifetime;
    std::shared_ptr<LinearPathMovement> pathMovement;
    bool isActive;

public:
    Meteor(std::shared_ptr<ModelLoader> model,
        std::shared_ptr<ShaderProgram> shader,
        std::shared_ptr<Material> material,
        MeteorType meteorType,
        const std::vector<glm::vec3>& path,
        float lifeDuration);

    bool shouldRemove() const;
    int getPoints() const { return points; }
    MeteorType getType() const { return type; }
    bool getIsActive() const { return isActive && !shouldRemove(); }
    void deactivate() { isActive = false; }
    float getRemainingTime() const;
};