#pragma once
#include "ShaderProgram.h"
#include "Shader.h"
#include "StructShaderSources.h"
#include <memory>
#include <unordered_map>

class ShaderManager {
private:
    static std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> shaders;

public:
    static std::shared_ptr<ShaderProgram> getShader(const std::string& name) {
        auto i = shaders.find(name);
        if (i != shaders.end()) {
            return i->second;
        }

        std::shared_ptr<ShaderProgram> newShader;

        if (name == "phong") {
            newShader = std::make_shared<ShaderProgram>(
                new Shader(GL_VERTEX_SHADER, ShaderSources::Phong.vertex.c_str()),
                new Shader(GL_FRAGMENT_SHADER, ShaderSources::Phong.fragment.c_str())
            );
        }
        else if (name == "constant") {
            newShader = std::make_shared<ShaderProgram>(
                new Shader(GL_VERTEX_SHADER, ShaderSources::Constant.vertex.c_str()),
                new Shader(GL_FRAGMENT_SHADER, ShaderSources::Constant.fragment.c_str())
            );
        }
        else if (name == "lamb") {
            newShader = std::make_shared<ShaderProgram>(
                new Shader(GL_VERTEX_SHADER, ShaderSources::Lamb.vertex.c_str()),
                new Shader(GL_FRAGMENT_SHADER, ShaderSources::Lamb.fragment.c_str())
            );
        }
        else if (name == "blinn") {
            newShader = std::make_shared<ShaderProgram>(
                new Shader(GL_VERTEX_SHADER, ShaderSources::Blinn.vertex.c_str()),
                new Shader(GL_FRAGMENT_SHADER, ShaderSources::Blinn.fragment.c_str())
            );
        }
        else if (name == "skybox") {
            newShader = std::make_shared<ShaderProgram>(
                new Shader(GL_VERTEX_SHADER, ShaderSources::Skybox.vertex.c_str()),
                new Shader(GL_FRAGMENT_SHADER, ShaderSources::Skybox.fragment.c_str())
            );
        }

        if (newShader) {
            shaders[name] = newShader;
        }

        return newShader;
    }

    static void initialize(){
        getShader("phong");
        getShader("constant");
        getShader("lamb");
        getShader("blinn");
        getShader("skybox");
    }

    static void clear() {
        shaders.clear();
    }
};