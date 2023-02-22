#include "voxel.h"

#include <glm/glm.hpp>

using namespace glm;

Voxel::Voxel(int x_offset, int y_offset, int z_offset) {
    this->defineVertices(x_offset, y_offset, z_offset);
    this->defineNormals();
    this->defineUVs();
}

Voxel::Voxel(int x_offset, int y_offset, int z_offset, std::vector<glm::vec2> uvs) {
    this->defineVertices(x_offset, y_offset, z_offset);
    this->defineNormals();
    
    UVs = uvs;
}

void Voxel::defineVertices(int x_offset, int y_offset, int z_offset) {
    vertices = {
        // Bottom face
        vec3(-0.5f + x_offset, -0.5f + y_offset, -0.5f + z_offset),
        vec3(0.5f + x_offset, -0.5f + y_offset, -0.5f + z_offset),
        vec3(-0.5f + x_offset, -0.5f + y_offset,  0.5f + z_offset),

        vec3(0.5f + x_offset, -0.5f + y_offset, -0.5f + z_offset),
        vec3(0.5f + x_offset, -0.5f + y_offset,  0.5f + z_offset),
        vec3(-0.5f + x_offset, -0.5f + y_offset,  0.5f + z_offset),

        // Top face
        vec3(-0.5f + x_offset,  0.5f + y_offset, -0.5f + z_offset),
        vec3(-0.5f + x_offset,  0.5f + y_offset,  0.5f + z_offset),
        vec3(0.5f + x_offset,  0.5f + y_offset, -0.5f + z_offset),

        vec3(0.5f + x_offset,  0.5f + y_offset, -0.5f + z_offset),
        vec3(-0.5f + x_offset,  0.5f + y_offset,  0.5f + z_offset),
        vec3(0.5f + x_offset,  0.5f + y_offset,  0.5f + z_offset),

        // Front face
        vec3(-0.5f + x_offset,  0.5f + y_offset,  0.5f + z_offset),
        vec3(-0.5f + x_offset, -0.5f + y_offset,  0.5f + z_offset),
        vec3(0.5f + x_offset,  0.5f + y_offset,  0.5f + z_offset),

        vec3(0.5f + x_offset,  0.5f + y_offset,  0.5f + z_offset),
        vec3(-0.5f + x_offset, -0.5f + y_offset,  0.5f + z_offset),
        vec3(0.5f + x_offset, -0.5f + y_offset,  0.5f + z_offset),

        // Back face
        vec3(-0.5f + x_offset,  0.5f + y_offset, -0.5f + z_offset),
        vec3(0.5f + x_offset,  0.5f + y_offset, -0.5f + z_offset),
        vec3(-0.5f + x_offset, -0.5f + y_offset, -0.5f + z_offset),

        vec3(0.5f + x_offset,  0.5f + y_offset, -0.5f + z_offset),
        vec3(0.5f + x_offset, -0.5f + y_offset, -0.5f + z_offset),
        vec3(-0.5f + x_offset, -0.5f + y_offset, -0.5f + z_offset),

        // Right face
        vec3(0.5f + x_offset,  0.5f + y_offset,   0.5f + z_offset),
        vec3(0.5f + x_offset, -0.5f + y_offset,   0.5f + z_offset),
        vec3(0.5f + x_offset,  0.5f + y_offset,  -0.5f + z_offset),

        vec3(0.5f + x_offset,  0.5f + y_offset,  -0.5f + z_offset),
        vec3(0.5f + x_offset, -0.5f + y_offset,   0.5f + z_offset),
        vec3(0.5f + x_offset, -0.5f + y_offset,  -0.5f + z_offset),

        // Left face
        vec3(-0.5f + x_offset,  0.5f + y_offset,  0.5f + z_offset),
        vec3(-0.5f + x_offset,  0.5f + y_offset, -0.5f + z_offset),
        vec3(-0.5f + x_offset, -0.5f + y_offset,  0.5f + z_offset),

        vec3(-0.5f + x_offset,  0.5f + y_offset, -0.5f + z_offset),
        vec3(-0.5f + x_offset, -0.5f + y_offset, -0.5f + z_offset),
        vec3(-0.5f + x_offset, -0.5f + y_offset,  0.5f + z_offset)
    };
}

void Voxel::defineNormals() {
    normals = {
        // Bottom face
        vec3(0.0f, -1.0f, 0.0f),
        vec3(0.0f, -1.0f, 0.0f),
        vec3(0.0f, -1.0f, 0.0f),

        vec3(0.0f, -1.0f, 0.0f),
        vec3(0.0f, -1.0f, 0.0f),
        vec3(0.0f, -1.0f, 0.0f),

        // Top face
        vec3(0.0f, 1.0f, 0.0f),
        vec3(0.0f, 1.0f, 0.0f),
        vec3(0.0f, 1.0f, 0.0f),

        vec3(0.0f, 1.0f, 0.0f),
        vec3(0.0f, 1.0f, 0.0f),
        vec3(0.0f, 1.0f, 0.0f),

        // Front face
        vec3(0.0f, 0.0f, 1.0f),
        vec3(0.0f, 0.0f, 1.0f),
        vec3(0.0f, 0.0f, 1.0f),

        vec3(0.0f, 0.0f, 1.0f),
        vec3(0.0f, 0.0f, 1.0f),
        vec3(0.0f, 0.0f, 1.0f),

        // Back face
        vec3(0.0f, 0.0f, -1.0f),
        vec3(0.0f, 0.0f, -1.0f),
        vec3(0.0f, 0.0f, -1.0f),

        vec3(0.0f, 0.0f, -1.0f),
        vec3(0.0f, 0.0f, -1.0f),
        vec3(0.0f, 0.0f, -1.0f),

        // Right face
        vec3(1.0f, 0.0f, 0.0f),
        vec3(1.0f, 0.0f, 0.0f),
        vec3(1.0f, 0.0f, 0.0f),

        vec3(1.0f, 0.0f, 0.0f),
        vec3(1.0f, 0.0f, 0.0f),
        vec3(1.0f, 0.0f, 0.0f),

        // Left face
        vec3(-1.0f, 0.0f, 0.0f),
        vec3(-1.0f, 0.0f, 0.0f),
        vec3(-1.0f, 0.0f, 0.0f),

        vec3(-1.0f, 0.0f, 0.0f),
        vec3(-1.0f, 0.0f, 0.0f),
        vec3(-1.0f, 0.0f, 0.0f)
    };
}

void Voxel::defineUVs() {
    UVs = {
        // Bottom face
        vec2(0.002f, 0.098f),
        vec2(0.098f, 0.098f),
        vec2(0.002f, 0.002f),

        vec2(0.098f, 0.098f),
        vec2(0.098f, 0.002f),
        vec2(0.002f, 0.002f),

        // Top face
        vec2(0.098f, 0.002f),
        vec2(0.098f, 0.098f),
        vec2(0.002f, 0.002f),

        vec2(0.002f, 0.002f),
        vec2(0.098f, 0.098f),
        vec2(0.002f, 0.098f),

        // Front face
        vec2(0.098f, 0.002f),
        vec2(0.098f, 0.098f),
        vec2(0.002f, 0.002f),

        vec2(0.002f, 0.002f),
        vec2(0.098f, 0.098f),
        vec2(0.002f, 0.098f),

        // Back face
        vec2(0.098f, 0.002f),
        vec2(0.002f, 0.002f),
        vec2(0.098f, 0.098f),

        vec2(0.002f, 0.002f),
        vec2(0.002f, 0.098f),
        vec2(0.098f, 0.098f),

        // Right face
        vec2(0.098f, 0.002f),
        vec2(0.098f, 0.098f),
        vec2(0.002f, 0.002f),

        vec2(0.002f, 0.002f),
        vec2(0.098f, 0.098f),
        vec2(0.002f, 0.098f),

        // Left face
        vec2(0.002f, 0.002f),
        vec2(0.098f, 0.002f),
        vec2(0.002f, 0.098f),

        vec2(0.098f, 0.002f),
        vec2(0.098f, 0.098f),
        vec2(0.002f, 0.098f)
    };
}

void Voxel::createContext() {
    Model::createContext();

    glGenBuffers(1, &modelMaterialsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, modelMaterialsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * materials.size(), &materials[0], GL_STATIC_DRAW);
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(5);
    glVertexAttribDivisor(5, 1);
}

Voxel::~Voxel() {
    Model::~Model();

    glDeleteBuffers(1, &modelMaterialsVBO);
}

void Voxel::buildObject(vec3 position, Material selectedMaterial, int GRID_SIZE, int x_quantized, int z_quantized) {
    positions.push_back(position);
    materials.push_back(selectedMaterial);
    objectsBuilt.push_back(0);
    if (objectsBuilt[x_quantized * GRID_SIZE + z_quantized] != -1) {
        objectsBuilt[x_quantized * GRID_SIZE + z_quantized] += 1;
    }
    addInBuiltPositions(x_quantized * GRID_SIZE + z_quantized, objectsBuilt.size() - 1);
}

void Voxel::destroyObject(int index, int position) {
    positions.erase(std::next(positions.begin(), position));
    materials.erase(std::next(materials.begin(), position));
    objectsBuilt.erase(std::next(objectsBuilt.begin(), position));
    removeFromBuiltPositions(index, --objectsBuilt[index]);

    for (int i = 0; i < builtPositions.size(); i++) {
        auto tuple = builtPositions[i];
        for (int j = 0; j < std::get<1>(tuple).size(); j++) {
            auto thisPosition = std::get<1>(tuple)[j];
            if (thisPosition >= position) {
                std::get<1>(builtPositions[i])[j]--;
            }
        }
    }
}

void Voxel::addInBuiltPositions(int index, int position) {
    auto it = std::find_if(builtPositions.begin(), builtPositions.end(), [index](const std::tuple<int, std::vector<int>>& e) {return std::get<0>(e) == index; });
    if (it != builtPositions.end()) {
        std::get<1>(*it).push_back(position);
    }
    else {
        builtPositions.push_back(std::make_tuple(index, std::vector<int>{position}));
    }
}

void Voxel::removeFromBuiltPositions(int index, int position) {
    auto it = std::find_if(builtPositions.begin(), builtPositions.end(), [index](const std::tuple<int, std::vector<int>>& e) {return std::get<0>(e) == index; });
    if (it != builtPositions.end()) {
        std::get<1>(*it).erase(std::next(std::get<1>(*it).begin(), position));
    }
}

int Voxel::getFromBuiltPositions(int index, int heightFound) {
    auto it = std::find_if(builtPositions.begin(), builtPositions.end(), [index](const std::tuple<int, std::vector<int>>& e) {return std::get<0>(e) == index; });
    if (it != builtPositions.end()) {
        return std::get<1>(*it)[heightFound-1];
    }
}