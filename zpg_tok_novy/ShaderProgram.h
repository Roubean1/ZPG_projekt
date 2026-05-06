#pragma once

#include "OpenGL_Include.h"
#include "Camera.h"
#include "Light.h"
#include "Shader.h"
#include "Material.h"

#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include <string>
#include <vector>
#include <memory>

class ShaderProgram {
private:
    GLuint programID = 0;

    GLint locModel = -1;
    GLint locView = -1;
    GLint locProjection = -1;

    GLuint createProgram(const Shader* vertexShader, const Shader* fragmentShader);

public:
    ShaderProgram() = default;
    ShaderProgram(const Shader* vertexShader,
        const Shader* fragmentShader);

    void useProgram() const;
    GLuint getProgramID() const { return programID; }

    void setUniform(const std::string& name, const glm::mat4& value) const;
    void setUniform(const std::string& name, const glm::vec3& value) const;
    void setUniform(const std::string& name, float value) const;
    void setUniform(const std::string& name, int value) const;

    void setCamera(Camera& camera);
    void setLights(const std::vector<std::shared_ptr<Light>>& lights) const;

    void setMaterialUniform(const std::shared_ptr<Material>& mat) const;

    ~ShaderProgram();
};