#ifndef PROGRAM_H
#define PROGRAM_H

#include <GL/glew.h>
#include <string>

class Program {
public:
	GLuint program;
	GLuint M, V, P;
	GLuint objectID;
	GLuint La, Ld, Ls, lightPosition, lightPower;
	GLuint textureAtlas;

	Program(std::string name, bool isObject);
};

#endif