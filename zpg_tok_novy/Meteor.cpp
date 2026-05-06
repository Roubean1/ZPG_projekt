#include "Meteor.h"

Meteor::Meteor(std::shared_ptr<ModelLoader> model,std::shared_ptr<ShaderProgram> shader,std::shared_ptr<Material> material,MeteorType meteorType,const std::vector<glm::vec3>& path,float lifeDuration)
    : DrawableObject(model, shader, material), type(meteorType), lifetime(lifeDuration), isActive(true) {

    spawnTime = static_cast<float>(glfwGetTime());

    switch (type) {
    case MeteorType::SMALL:      points = 1; break;
    case MeteorType::LARGE:      points = 2; break;
    case MeteorType::DANGEROUS:  points = -3; break;
    case MeteorType::BONUS:      points = 5; break;
    }

    float speed = 1.0f + (static_cast<float>(rand()) / RAND_MAX) * 2.0f;

    pathMovement = std::make_shared<LinearPathMovement>(path, speed);

    auto compositeTransform = std::make_shared<CompositeTransform>();
    compositeTransform->addTransform(pathMovement);

    getTransformations()->addTransform(compositeTransform);
}

bool Meteor::shouldRemove() const {
    float currentTime = static_cast<float>(glfwGetTime());
    bool timeExpired = (currentTime - spawnTime) >= lifetime;
    bool movementComplete = (pathMovement && pathMovement->isComplete());

    return timeExpired || movementComplete;
}

float Meteor::getRemainingTime() const {
    float currentTime = static_cast<float>(glfwGetTime());

    return std::max(0.0f, lifetime - (currentTime - spawnTime));
}