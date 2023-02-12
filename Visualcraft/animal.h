#ifndef ANIMAL_H
#define ANIMAL_H

#include <vector>

#include "model.h"
#include "voxel.h"

class Animal : public Model {
public:
	Animal();

public:
	std::vector<Voxel*> voxels;
};

#endif