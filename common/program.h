#ifndef PROGRAM_H
#define PROGRAM_H

#include <GL/glew.h>
#include <string>

class BaseProgram {
public:
	GLuint program;

	BaseProgram(std::string name);
};

class Program : public BaseProgram {
public:
	GLuint M, V, P;
	GLuint objectID;

	Program(std::string name, bool isObject);
};

class DepthProgram : public Program {
public:
	DepthProgram(std::string name, bool isObject);
};

class LightProgram : public Program {
public:
	GLuint La, Ld, Ls, lightPosition, lightPower;
	GLuint textureAtlas;
	
	GLuint depthMap;
	GLuint lightVP;

	LightProgram(std::string name, bool isObject);
};

class DepthMapProgram : public BaseProgram {
public:
	GLuint texture;

	DepthMapProgram(std::string name);
};

#endif