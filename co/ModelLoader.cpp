#include "ModelLoader.h"
#include "tiny_obj_loader.h"
#include <stdexcept>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

ModelLoader::ModelLoader(const std::string& name) {
    std::string inputfile = "assets/" + name;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err,
        inputfile.c_str(), "assets/");

    if (!warn.empty()) std::cout << "Warn: " << warn << std::endl;
    if (!err.empty()) std::cerr << "Err: " << err << std::endl;
    if (!ret) throw std::runtime_error("Failed to load OBJ file: " + inputfile);

    std::vector<float> vertices;

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

            if (index.normal_index >= 0) {
                vertices.push_back(attrib.normals[3 * index.normal_index + 0]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 1]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 2]);
            }
            else {
                vertices.insert(vertices.end(), { 0.0f, 1.0f, 0.0f });
            }

            if (index.texcoord_index >= 0) {
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
            }
            else {
                vertices.insert(vertices.end(), { 0.0f, 0.0f });
            }
        }
    }

    vertexCount = static_cast<int>(vertices.size() / 8);
    std::cout << "Model loaded: " << inputfile << " (" << vertexCount << " vertices)\n";

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glBindVertexArray(0);
}

void ModelLoader::draw() const {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}

std::shared_ptr<ModelLoader> ModelLoader::load(const std::string& filename) {
    try {
        return std::shared_ptr<ModelLoader>(new ModelLoader(filename));
    }
    catch (const std::exception& e) {
        std::cerr << "ModelLoader::load() error: " << e.what() << std::endl;
        return nullptr;
    }
}

