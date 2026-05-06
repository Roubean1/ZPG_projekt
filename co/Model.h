#pragma once
#include "OpenGL_Include.h"
#include <vector>

class Model {
private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    int vertexCount = 0;
    bool hasUVs = false;

public:
    Model() = default;
    void loadModel(const float* vertices, int vertexCount, int stride = 6);
    void loadModelWithUVs(const float* vertices, int vertexCount, int stride = 8);
    void draw() const;
    bool hasTextureCoordinates() const { return hasUVs; }
    ~Model();
};