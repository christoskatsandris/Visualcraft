#include "animal.h"
#include <glm/glm.hpp>

using namespace glm;

Animal::Animal() {
	voxels.push_back(
		new Voxel(0, 0, 0, {
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
            vec2(0.098f + 0.3f, 0.002f + 0.0f),
            vec2(0.002f + 0.1f, 0.002f + 0.0f),
            vec2(0.098f + 0.3f, 0.098f + 0.1f),

            vec2(0.002f + 0.1f, 0.002f + 0.0f),
            vec2(0.002f + 0.1f, 0.098f + 0.1f),
            vec2(0.098f + 0.3f, 0.098f + 0.1f),

            // Right face
            vec2(0.098f + 0.0f, 0.002f + 0.0f),
            vec2(0.098f + 0.1f, 0.098f + 0.1f),
            vec2(0.002f + 0.0f, 0.002f + 0.0f),

            vec2(0.002f + 0.0f, 0.002f + 0.0f),
            vec2(0.098f + 0.1f, 0.098f + 0.1f),
            vec2(0.002f + 0.1f, 0.098f + 0.1f),

            // Left face
            vec2(0.002f + 0.3f, 0.002f + 0.0f),
            vec2(0.098f + 0.3f, 0.002f + 0.0f),
            vec2(0.002f + 0.3f, 0.098f + 0.1f),

            vec2(0.098f + 0.3f, 0.002f + 0.0f),
            vec2(0.098f + 0.3f, 0.098f + 0.1f),
            vec2(0.002f + 0.3f, 0.098f + 0.1f)
			})
	);

	//voxels.push_back(
	//	new Voxel(1, 0, 0, {
 //           // Bottom face
 //           vec2(0.002f, 0.098f),
 //           vec2(0.098f, 0.098f),
 //           vec2(0.002f, 0.002f),

 //           vec2(0.098f, 0.098f),
 //           vec2(0.098f, 0.002f),
 //           vec2(0.002f, 0.002f),

 //           // Top face
 //           vec2(0.098f, 0.002f),
 //           vec2(0.098f, 0.098f),
 //           vec2(0.002f, 0.002f),

 //           vec2(0.002f, 0.002f),
 //           vec2(0.098f, 0.098f),
 //           vec2(0.002f, 0.098f),

 //           // Front face
 //           vec2(0.098f, 0.002f),
 //           vec2(0.098f, 0.098f),
 //           vec2(0.002f, 0.002f),

 //           vec2(0.002f, 0.002f),
 //           vec2(0.098f, 0.098f),
 //           vec2(0.002f, 0.098f),

 //           // Back face
 //           vec2(0.098f + 0.1f, 0.002f),
 //           vec2(0.002f + 0.1f, 0.002f),
 //           vec2(0.098f + 0.1f, 0.098f),

 //           vec2(0.002f + 0.1f, 0.002f),
 //           vec2(0.002f + 0.1f, 0.098f),
 //           vec2(0.098f + 0.1f, 0.098f),

 //           // Right face
 //           vec2(0.098f, 0.002f),
 //           vec2(0.098f, 0.098f),
 //           vec2(0.002f, 0.002f),

 //           vec2(0.002f, 0.002f),
 //           vec2(0.098f, 0.098f),
 //           vec2(0.002f, 0.098f),

 //           // Left face
 //           vec2(0.002f, 0.002f),
 //           vec2(0.098f, 0.002f),
 //           vec2(0.002f, 0.098f),

 //           vec2(0.098f, 0.002f),
 //           vec2(0.098f, 0.098f),
 //           vec2(0.002f, 0.098f)
 //           })
	//		})
	//);

	for (int i = 0; i < voxels.size(); i++) {
		vertices.insert(vertices.end(), voxels[i]->vertices.begin(), voxels[i]->vertices.end());
		normals.insert(normals.end(), voxels[i]->normals.begin(), voxels[i]->normals.end());
		UVs.insert(UVs.end(), voxels[i]->UVs.begin(), voxels[i]->UVs.end());
	}
}