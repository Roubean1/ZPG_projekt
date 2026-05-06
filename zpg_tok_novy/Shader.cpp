#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

void Shader::compileShader(GLenum shaderType, const char* source) {
    shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &source, nullptr);
    glCompileShader(shaderID);

    GLint status = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> infoLog(infoLogLength);
        glGetShaderInfoLog(shaderID, infoLogLength, nullptr, infoLog.data());
        std::cerr << " Shader compile error:\n" << infoLog.data() << std::endl;
    }
}

Shader::Shader(GLenum shaderType, const char* shaderFile) {
    std::ifstream file(shaderFile);
    if (!file.is_open()) {
        std::cerr << " Error: Cannot open shader file " << shaderFile << std::endl;
        exit(1);
    }

    std::string shaderCode((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    file.close();

    std::cout << " Compiling shader from file: " << shaderFile << std::endl;
    compileShader(shaderType, shaderCode.c_str());
}

void Shader::attachShader(GLuint shaderProgram) const {
    glAttachShader(shaderProgram, shaderID);
}

void validateProgram(GLuint programID) {
    glValidateProgram(programID);
    GLint validated = GL_FALSE;
    glGetProgramiv(programID, GL_VALIDATE_STATUS, &validated);

    if (validated == GL_FALSE) {
        GLint logLen = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLen);
        std::vector<GLchar> log(logLen);
        glGetProgramInfoLog(programID, logLen, nullptr, log.data());
        std::cerr << " Shader program validation failed:\n" << log.data() << std::endl;
    }
}
