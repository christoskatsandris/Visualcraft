#include "model.h"

#include <vector>
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <common/camera.h>
#include <common/light.h>
#include <common/program.h>

using namespace glm;

void Model::createContext(std::vector<vec3> modelPositions, std::vector<float> modelHeightMap) {
    glGenVertexArrays(1, &modelVAO);
    glBindVertexArray(modelVAO);

    glGenBuffers(1, &modelVerticesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, modelVerticesVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &modelNormalsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, modelNormalsVBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &modelUVsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, modelUVsVBO);
    glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(vec2), &UVs[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &modelPositionsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, modelPositionsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * modelPositions.size(), &modelPositions[0][0], GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1);

    glGenBuffers(1, &modelHeightMapVBO);
    glBindBuffer(GL_ARRAY_BUFFER, modelHeightMapVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * modelHeightMap.size(), &modelHeightMap[0], GL_STATIC_DRAW);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(4);
    glVertexAttribDivisor(4, 1);
}

void Model::evaluateMap(int grid_size) {
    hasLocated = std::vector<bool>(grid_size * grid_size, false);

    for (int i = 0; i < positions.size(); i++) {
        hasLocated[(positions[i].x + grid_size / 2) * grid_size + (positions[i].z + grid_size / 2)] = true;
    }
}

void Model::bind() {
    glBindVertexArray(modelVAO);
}

void Model::render(Program* shader, Camera* camera, mat4 modelMatrix, int objectID, GLuint textureAtlas, Light* light, int count) {
    glUseProgram(shader->program);
    this->bind();

    glUniformMatrix4fv(shader->P, 1, GL_FALSE, &camera->projectionMatrix[0][0]);
    glUniformMatrix4fv(shader->V, 1, GL_FALSE, &camera->viewMatrix[0][0]);
    glUniformMatrix4fv(shader->M, 1, GL_FALSE, &modelMatrix[0][0]);

    light->uploadToShader(shader->La, shader->Ld, shader->Ls, shader->lightPosition, shader->lightPower);

    if (objectID != NULL) {
        glUniform1i(shader->objectID, objectID);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureAtlas);
    glUniform1i(shader->textureAtlas, 0);

    glDrawArraysInstanced(GL_TRIANGLES, 0, this->vertices.size(), count);

}

//void Model::render(GLuint program, GLuint projectionMatrixLocation, GLuint viewMatrixLocation, GLuint modelMatrixLocation, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::mat4 modelMatrix,
//    int id, GLuint objectIDLocation, GLuint textureAtlas, GLuint textureAtlasSampler, Light* light, GLuint LaLocation, GLuint LdLocation, GLuint LsLocation, GLuint lightPositionLocation, GLuint lightPowerLocation, int count
//) {
//    glUseProgram(program);
//    this->bind();
//
//    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
//    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
//    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);
//
//    light->uploadToShader(LaLocation, LdLocation, LsLocation, lightPositionLocation, lightPowerLocation);
//
//    if (id != NULL) {
//        glUniform1i(objectIDLocation, id);
//    }
//
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, textureAtlas);
//    glUniform1i(textureAtlasSampler, 0);
//
//    glDrawArraysInstanced(GL_TRIANGLES, 0, this->vertices.size(), count);
//
//}

Model::~Model() {
    glDeleteBuffers(1, &modelVerticesVBO);
    glDeleteBuffers(1, &modelNormalsVBO);
    glDeleteBuffers(1, &modelUVsVBO);
    glDeleteBuffers(1, &modelPositionsVBO);
    glDeleteBuffers(1, &modelHeightMapVBO);
    glDeleteVertexArrays(1, &modelVAO);
}