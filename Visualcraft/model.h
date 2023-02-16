#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <common/camera.h>
#include <common/light.h>
#include <common/program.h>

class Model {
private:
	GLuint modelVAO, modelVerticesVBO, modelNormalsVBO, modelUVsVBO, modelPositionsVBO, modelHeightMapVBO;

public:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;

	std::vector<bool> hasLocated;
	std::vector<glm::vec3> positions;
	std::vector<float> heightMap;

public:
	void createContext(std::vector<glm::vec3> modelPositions, std::vector<float> modelHeightMap);
	void evaluateMap(int grid_size);
	void bind();
	void render(Program* shader, Camera* camera, glm::mat4 modelMatrix, int objectID, GLuint textureAtlas, Light* light, int count);
	//void render(GLuint program, GLuint projectionMatrixLocation, GLuint viewMatrixLocation, GLuint modelMatrixLocation, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::mat4 modelMatrix,
	//	int id, GLuint objectIDLocation, GLuint textureAtlas, GLuint textureAtlasSampler, Light* light, GLuint LaLocation, GLuint LdLocation, GLuint LsLocation, GLuint lightPositionLocation, GLuint lightPowerLocation, int count
	//);
	~Model();
};

#endif