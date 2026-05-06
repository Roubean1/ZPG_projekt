#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"

Texture::Texture(const std::string& filename, bool flipVertical) : filepath(filename) {
    stbi_set_flip_vertically_on_load(flipVertical);

    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 4);
    if (!data) {
        std::cerr << "Error loading texture: " << filename << std::endl;
        return;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    std::cout << "Texture loaded: " << filename << " (" << width << "x" << height << ")" << std::endl;
}

Texture::Texture(const std::vector<std::string>& faces, bool flipVertical) : isCubemap(true) {
    stbi_set_flip_vertically_on_load(flipVertical);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for (unsigned int i = 0; i < faces.size(); i++) {
        std::string fullPath = "assets/" + faces[i];
        unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &channels, 0);
        if (data) {
            GLenum format = GL_RGB;
            if (channels == 4) format = GL_RGBA;
            else if (channels == 1) format = GL_RED;
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            std::cerr << "Failed to load cubemap face " << i << ": " << fullPath << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    std::cout << "Cubemap loaded" << std::endl;
}

Texture::~Texture() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
    }
}

void Texture::bind(GLuint textureUnit) const {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    if (isCubemap) {
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    }
    else {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}