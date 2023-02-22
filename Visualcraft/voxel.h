#ifndef VOXEL_H
#define VOXEL_H

#include <vector>
#include <tuple>
#include <glm/glm.hpp>

#include "model.h"

class Voxel : public Model {
public:
	std::vector<Material> materials;
	std::vector<int> objectsBuilt;
	std::vector<std::tuple<int, std::vector<int>>> builtPositions; // a vector of tuples. One tuple for each index of Voxel::objectsBuilt > 0.
																   // Each tuple contains the index of Voxel::objectsBuilt and a vector of int
																   // that contains the indices of each object in Voxel::positions.
	GLuint modelMaterialsVBO;

public:
	Voxel(int x_offset, int y_offset, int z_offset);
	Voxel(int x_offset, int y_offset, int z_offset, std::vector<glm::vec2> uvs);
	void defineVertices(int x_offset, int y_offset, int z_offset);
	void defineNormals();
	void defineUVs();
	void createContext();
	void buildObject(glm::vec3 position, Material selectedMaterial, int GRID_SIZE, int x_quantized, int z_quantized);
	void destroyObject(int index, int position);
	int getFromBuiltPositions(int index, int heightFound);
	void addInBuiltPositions(int index, int position);
	void removeFromBuiltPositions(int index, int position);
	~Voxel();
};

#endif