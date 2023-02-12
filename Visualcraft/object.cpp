#include <iostream>
#include "glm/glm.hpp"

#include "object.h"
#include "common/model.h"
#include <algorithm>

bool compareX(const glm::vec3& s1, const glm::vec3& s2);
bool compareY(const glm::vec3& s1, const glm::vec3& s2);
bool compareZ(const glm::vec3& s1, const glm::vec3& s2);

Object::Object(std::string path, int xsize, int ysize, int zsize, int vertex_threshold) {
	this->voxelize(path, xsize, ysize, zsize, vertex_threshold);
}

void Object::voxelize(std::string path, int xsize, int ysize, int zsize, int vertex_threshold) {
	Drawable* model = new Drawable(path);

	auto maxX = std::max_element(model->vertices.begin(), model->vertices.end(), compareX);
	auto maxY = std::max_element(model->vertices.begin(), model->vertices.end(), compareY);
	auto maxZ = std::max_element(model->vertices.begin(), model->vertices.end(), compareZ);
	auto minX = std::min_element(model->vertices.begin(), model->vertices.end(), compareX);
	auto minY = std::min_element(model->vertices.begin(), model->vertices.end(), compareY);
	auto minZ = std::min_element(model->vertices.begin(), model->vertices.end(), compareZ);

	float xrange = (*maxX).x - (*minX).x;
	float yrange = (*maxY).y - (*minY).y;
	float zrange = (*maxZ).z - (*minZ).z;

	float xstep = xrange / xsize;
	float ystep = yrange / ysize;
	float zstep = zrange / zsize;

	for (int y = 0; y < ysize; y++) {
		for (int x = 0; x < xsize; x++) {
			for (int z = 0; z < zsize; z++) {
				float currXmin = (*minX).x + x * xstep;
				float currXmax = currXmin + xstep;
				float currYmin = (*minY).y + y * ystep;
				float currYmax = currYmin + ystep;
				float currZmin = (*minZ).z + z * zstep;
				float currZmax = currZmin + zstep;

				auto cntr = std::count_if(model->vertices.begin(), model->vertices.end(),
					[currXmin, currXmax, currYmin, currYmax, currZmin, currZmax](const glm::vec3& vertex) {
						return vertex.x >= currXmin && vertex.x <= currXmax
						&& vertex.y >= currYmin && vertex.y <= currYmax
					&& vertex.z >= currZmin && vertex.z <= currZmax;
					}
				);

				std::cout << "Vertices in (" << x << ", " << y << ", " << z << "): " << cntr << std::endl;

				if (cntr > vertex_threshold) {
					voxels.push_back(new Voxel(x, y, z));
				}
			}
		}
	}

	delete model;

	for (int i = 0; i < voxels.size(); i++) {
		vertices.insert(vertices.end(), voxels[i]->vertices.begin(), voxels[i]->vertices.end());
		normals.insert(normals.end(), voxels[i]->normals.begin(), voxels[i]->normals.end());
		UVs.insert(UVs.end(), voxels[i]->UVs.begin(), voxels[i]->UVs.end());
	}
}

bool compareX(const glm::vec3& s1, const glm::vec3& s2) {
	return s1.x < s2.x;
}

bool compareY(const glm::vec3& s1, const glm::vec3& s2) {
	return s1.y < s2.y;
}

bool compareZ(const glm::vec3& s1, const glm::vec3& s2) {
	return s1.z < s2.z;
}
