#pragma once

#include "StructShaderSources.h"
#include "Material.h"
#include <vector>
#include <memory>

#include "OpenGL_Include.h"
#include "ShaderProgram.h"
#include "CompositeTransform.h"
#include "Shader.h"
#include "Model.h"
#include "ModelLoader.h"
#include "Texture.h"
#include "Translate.h"
#include "Scale.h"

class DrawableObject {
protected:
    std::shared_ptr<Model> model;
    std::shared_ptr<ModelLoader> modelLoader;
    std::shared_ptr<ShaderProgram> shaderProgram;
    std::shared_ptr<CompositeTransform> transformations;
    std::shared_ptr<Material> material;
    std::shared_ptr<Texture> texture;
    size_t verticesNum = 0;
    unsigned int id = 0;
    glm::vec3 position = glm::vec3(0.0f);

public:
    DrawableObject(const float* points,
        size_t verticesNum,
        int stride,
        std::shared_ptr<ShaderProgram> shader,
        std::shared_ptr<Material> mat = nullptr,
        std::shared_ptr<Texture> tex = nullptr);

    DrawableObject(std::shared_ptr<ModelLoader> loader,
        std::shared_ptr<ShaderProgram> shader,
        std::shared_ptr<Material> mat = nullptr,
        std::shared_ptr<Texture> tex = nullptr);

    void draw();

    std::shared_ptr<CompositeTransform> getTransformations() { return transformations; }
    std::shared_ptr<ShaderProgram> getShaderProgram() const { return shaderProgram; }
    std::shared_ptr<Material> getMaterial() { return material; }

    void setTexture(std::shared_ptr<Texture> tex) { texture = tex; }
    void setShaderProgram(std::shared_ptr<ShaderProgram> shader) { shaderProgram = shader; }
    void setId(unsigned int newId) { id = newId; }
    unsigned int getId() const { return id; }

    void setPosition(const glm::vec3& newPos) {
        position = newPos;
        auto newTransforms = std::make_shared<CompositeTransform>();
        newTransforms->addTransform(std::make_shared<Translate>(position));
        transformations = newTransforms;
    }
    glm::vec3 getPosition() const { return position; }
};