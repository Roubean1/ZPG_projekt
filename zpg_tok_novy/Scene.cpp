#include "Scene.h"

void Scene::draw() {
    ShaderProgram* lastShader = nullptr;

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    for (auto& obj : objects) {
        if (!obj) continue;

        unsigned int objId = obj->getId();
        glStencilFunc(GL_ALWAYS, objId, 0xFF);

        auto shaderPtr = obj->getShaderProgram();
        if (!shaderPtr) {
            obj->draw();
            continue;
        }

        ShaderProgram* shader = shaderPtr.get();

        if (shader != lastShader) {
            shader->useProgram();

            if (camera) {
                shader->setCamera(*camera);
            }
            shader->setLights(lights);

            lastShader = shader;
        }

        obj->draw();
    }

    glDisable(GL_STENCIL_TEST);
}