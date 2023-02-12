#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>

#include "model.h"
#include "voxel.h"

class Object : public Model {
public:
	Object(std::string path, int xsize, int ysize, int zsize, int vertex_threshold);
	void voxelize(std::string path, int xsize, int ysize, int zsize, int vertex_threshold);

public:
	std::vector<Voxel*> voxels;
};

#endif