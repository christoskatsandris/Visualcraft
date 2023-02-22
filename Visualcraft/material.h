#ifndef MATERIAL_H
#define MATERIAL_H

enum Material {
	// This is a translation from GLFW_KEY_X to their #define expansion, e.g. GLFW_KEY_1 expands to 49.
	DEFAULT_MATERIAL = 0,
	BRICK = 49,
	GLASS = 50,
	CONCRETE = 51,
	WHEAT = 52,
	GRASS = 53,
	SAND = 54,
	STONE = 55
};

#endif