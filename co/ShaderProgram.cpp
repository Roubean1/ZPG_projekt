#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

GLuint ShaderProgram::createProgram(const Shader* vertexShader, const Shader* fragmentShader) {
    GLuint id = glCreateProgram();
    vertexShader->attachShader(id);
    fragmentShader->attachShader(id);

    glLinkProgram(id);

    GLint status;
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<GLchar> infoLog(infoLogLength);
        glGetProgramInfoLog(id, infoLogLength, nullptr, infoLog.data());
        std::cerr << "Shader program link failure:\n" << infoLog.data() << std::endl;
    }

    return id;
}

ShaderProgram::ShaderProgram(const Shader* vertexShader, const Shader* fragmentShader)
{
    programID = createProgram(vertexShader, fragmentShader);

    useProgram();

    locModel = glGetUniformLocation(programID, "modelMatrix");
    locView = glGetUniformLocation(programID, "viewMatrix");
    locProjection = glGetUniformLocation(programID, "projectionMatrix");
}

void ShaderProgram::useProgram() const {
    glUseProgram(programID);
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat4& value) const {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    if (loc != -1) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    }
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec3& value) const {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    if (loc != -1) {
        glUniform3fv(loc, 1, glm::value_ptr(value));
    }
}

void ShaderProgram::setUniform(const std::string& name, float value) const {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    if (loc != -1) {
        glUniform1f(loc, value);
    }
}

void ShaderProgram::setUniform(const std::string& name, int value) const {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    if (loc != -1) {
        glUniform1i(loc, value);
    }
}

void ShaderProgram::setCamera( Camera& camera) {
    useProgram();

    glm::mat4 viewMatrix = camera.getViewMatrix();
    glm::mat4 projectionMatrix = camera.getProjectionMatrix();

    if (locView != -1) {
        glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    }

    if (locProjection != -1) {
        glUniformMatrix4fv(locProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    }

    GLint locViewPos = glGetUniformLocation(programID, "viewPosition");
    if (locViewPos != -1) {
        auto cameraPos = camera.getPosition();
        glUniform3fv(locViewPos, 1, glm::value_ptr(cameraPos));
    }
}

void ShaderProgram::setLights(const std::vector<std::shared_ptr<Light>>& lights) const {
    if (lights.empty()) return;

    useProgram();

    GLint locNumLights = glGetUniformLocation(programID, "numLights");
    if (locNumLights != -1) {
        glUniform1i(locNumLights, static_cast<int>(lights.size()));
    }

    for (size_t i = 0; i < lights.size(); ++i) {
        if (!lights[i]) continue;

        std::string base = "lights[" + std::to_string(i) + "].";

        glm::vec3 lightColor = lights[i]->getIsOn()
            ? lights[i]->getColor()
            : glm::vec3(0.0f);

        glUniform1i(glGetUniformLocation(programID, (base + "type").c_str()), static_cast<int>(lights[i]->getType()));
        glUniform3fv(glGetUniformLocation(programID, (base + "color").c_str()), 1, glm::value_ptr(lightColor));

        switch (lights[i]->getType()) {
            case LightType::AMBIENT: {
                glUniform3fv(glGetUniformLocation(programID, (base + "position").c_str()), 1, glm::value_ptr(glm::vec3(0.0f)));
                glUniform3fv(glGetUniformLocation(programID, (base + "direction").c_str()), 1, glm::value_ptr(glm::vec3(0.0f)));
                break;
            }

            case LightType::POINT: {
                auto* p = static_cast<PointLight*>(lights[i].get());
                glUniform3fv(glGetUniformLocation(programID, (base + "position").c_str()), 1, glm::value_ptr(p->getPosition()));
                glUniform1f(glGetUniformLocation(programID, (base + "constant").c_str()), p->getConstant());
                glUniform1f(glGetUniformLocation(programID, (base + "linear").c_str()), p->getLinear());
                glUniform1f(glGetUniformLocation(programID, (base + "quadratic").c_str()), p->getQuadratic());
                break;
            }

            case LightType::DIRECTIONAL: {
                auto* d = static_cast<DirectionalLight*>(lights[i].get());
                glUniform3fv(glGetUniformLocation(programID, (base + "direction").c_str()), 1, glm::value_ptr(d->getDirection()));
                break;
            }

            case LightType::SPOT: {
                auto* s = static_cast<SpotLight*>(lights[i].get());
                glUniform3fv(glGetUniformLocation(programID, (base + "position").c_str()), 1, glm::value_ptr(s->getPosition()));
                glUniform3fv(glGetUniformLocation(programID, (base + "direction").c_str()), 1, glm::value_ptr(s->getDirection()));
                glUniform1f(glGetUniformLocation(programID, (base + "cutOff").c_str()), s->getCutOff());
                glUniform1f(glGetUniformLocation(programID, (base + "outerCutOff").c_str()), s->getOuterCutOff());
                glUniform1f(glGetUniformLocation(programID, (base + "constant").c_str()), s->getConstant());
                glUniform1f(glGetUniformLocation(programID, (base + "linear").c_str()), s->getLinear());
                glUniform1f(glGetUniformLocation(programID, (base + "quadratic").c_str()), s->getQuadratic());
                break;
            }
        }
    }
}

void ShaderProgram::setMaterialUniform(const std::shared_ptr<Material>& mat) const {
    if (!mat) return;
    useProgram();

    setUniform("material.ambient", mat->ambient);
    setUniform("material.diffuse", mat->diffuse);
    setUniform("material.specular", mat->specular);
    setUniform("material.shininess", mat->shininess);
}

ShaderProgram::~ShaderProgram() {
    if (programID != 0) {
        glDeleteProgram(programID);
    }
}