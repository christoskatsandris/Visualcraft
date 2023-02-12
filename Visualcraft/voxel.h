#ifndef VOXEL_H
#define VOXEL_H

#include <vector>
#include <glm/glm.hpp>

#include "model.h"

class Voxel : public Model {
public:
	Voxel(int x_offset, int y_offset, int z_offset);
	Voxel(int x_offset, int y_offset, int z_offset, std::vector<glm::vec2> uvs);
	void defineVertices(int x_offset, int y_offset, int z_offset);
	void defineNormals();
	void defineUVs();
};

#endif