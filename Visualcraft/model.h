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
	void createContext();
	void evaluateMap(int grid_size);
	void bind();
	void render(bool renderLight, Program* shader, glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, int objectID, int rayCastedID, GLuint textureAtlas, Light* light, int count);
	~Model();
};

#endif