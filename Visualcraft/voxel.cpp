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