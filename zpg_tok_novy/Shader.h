#pragma once
#include <GL/glew.h>
#include <string>

class Shader {
private:
    GLuint shaderID = 0;
    void compileShader(GLenum shaderType, const char* source);

public:
    Shader(GLenum shaderType, const char* shaderFile);
    void attachShader(GLuint shaderProgram) const;
};
