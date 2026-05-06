#pragma once
#include "OpenGL_Include.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

class ModelLoader : public std::enable_shared_from_this<ModelLoader> {
private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    int vertexCount = 0;

protected:
    explicit ModelLoader(const std::string& name);

public:
    void draw() const;
    static std::shared_ptr<ModelLoader> load(const std::string& filename);
};
