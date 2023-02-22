#ifndef MATERIAL_H
#define MATERIAL_H

enum Material {
	// This is a translation from GLFW_KEY_X to their #define expansion, e.g. GLFW_KEY_1 expands to 49.
	DEFAULT_MATERIAL = 0,
	BRICK = 49,
	GLASS = 50,
	CONCRETE = 51,
	GRASS = 52,
	SAND = 53,
	STONE = 54
};

#endif