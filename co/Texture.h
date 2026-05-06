#pragma once
#include "OpenGL_Include.h"
#include <string>
#include <iostream>
#include <vector>

class Texture {
private:
    GLuint textureID = 0;
    int width = 0;
    int height = 0;
    int channels = 0;
    std::string filepath;
    bool isCubemap = false;

public:
    Texture(const std::string& filename, bool flipVertical = true); // texture

    Texture(const std::vector<std::string>& faces, bool flipVertical = false); //skybox

    ~Texture();

    void bind(GLuint textureUnit = 0) const;
    void unbind() const;

    GLuint getID() const { return textureID; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    bool getIsCubemap() const { return isCubemap; }
};