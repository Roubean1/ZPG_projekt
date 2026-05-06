#include "DrawableObject.h"
#include <iostream>

DrawableObject::DrawableObject(
    const float* points,
    size_t verticesNum,
    int stride,
    std::shared_ptr<ShaderProgram> shader,
    std::shared_ptr<Material> mat,
    std::shared_ptr<Texture> tex)
    :
    shaderProgram(shader),
    transformations(std::make_shared<CompositeTransform>()),
    material(mat),
    texture(tex),
    verticesNum(verticesNum)
{
    model = std::make_shared<Model>();

    model->loadModel(points, static_cast<int>(verticesNum), stride);

    std::cout << "DrawableObject created: " << verticesNum << " vertices, stride: " << stride << std::endl;
}

DrawableObject::DrawableObject(std::shared_ptr<ModelLoader> loader,
    std::shared_ptr<ShaderProgram> shader,
    std::shared_ptr<Material> mat,
    std::shared_ptr<Texture> tex)
    :
    modelLoader(loader),
    shaderProgram(shader),
    transformations(std::make_shared<CompositeTransform>()),
    material(mat),
    texture(tex)
{
    std::cout << "ModelLoader drawable created" << (texture ? " with texture" : " (no texture)") << std::endl;
}

void DrawableObject::draw()
{
    if (!shaderProgram) {
        std::cerr << "DrawableObject: no ShaderProgram set!" << std::endl;
        return;
    }

    if (material) shaderProgram->setMaterialUniform(material);

    if (texture) {
        texture->bind(0);
        shaderProgram->setUniform("textureUnitID", 0);
        shaderProgram->setUniform("useTexture", 1);
    }
    else {
        shaderProgram->setUniform("useTexture", 0);
    }

    if (transformations)
        shaderProgram->setUniform("modelMatrix", transformations->getMatrix());

    if (modelLoader) modelLoader->draw();
    else if (model)  model->draw();
    else std::cerr << "DrawableObject: no model data!" << std::endl;

    if (texture) texture->unbind();
}
