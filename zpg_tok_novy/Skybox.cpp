#include "Skybox.h"
#include <iostream>

float skyboxVertices[] = {
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};


Skybox::Skybox(std::shared_ptr<Camera> camera, const std::vector<std::string>& textureFiles)
    : camera(camera)
{
    cubemapTexture = std::make_shared<Texture>(textureFiles, false);

    // Použijte ShaderManager místo pøímého vytváøení
    shaderProgram = ShaderManager::getShader("skybox");
    if (!shaderProgram) {
        std::cerr << "Failed to get skybox shader!" << std::endl;
        return;
    }

    skyboxObject = std::make_shared<DrawableObject>(
        skyboxVertices,
        sizeof(skyboxVertices) / (3 * sizeof(float)),
        3,
        shaderProgram,
        nullptr,
        cubemapTexture
    );

    shaderProgram->useProgram();
    shaderProgram->setUniform("skybox", 0);

    std::cout << "Skybox initialized" << std::endl;
}

void Skybox::draw() {
    if (!camera || !shaderProgram || !skyboxObject) return;

    glDepthFunc(GL_LEQUAL);

    shaderProgram->useProgram();

    glm::mat4 view = glm::mat4(glm::mat3(camera->getViewMatrix()));
    shaderProgram->setUniform("viewMatrix", view);
    shaderProgram->setUniform("projectionMatrix", camera->getProjectionMatrix());

    skyboxObject->draw();

    glDepthFunc(GL_LESS);
}