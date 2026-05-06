#pragma once
#include "DrawableObject.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Camera.h"
#include "StructShaderSources.h"
#include "ShaderManager.h"

class Skybox {
private:
    std::shared_ptr<DrawableObject> skyboxObject;
    std::shared_ptr<Texture> cubemapTexture;
    std::shared_ptr<ShaderProgram> shaderProgram;
    std::shared_ptr<Camera> camera;

public:
    Skybox(std::shared_ptr<Camera> camera, const std::vector<std::string>& textureFiles);
    void draw();
};