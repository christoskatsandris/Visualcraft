#include "program.h"
#include "shader.h"
#include <string>

using namespace std;

Program::Program(string name, bool isObject) {
	program = loadShaders((name+".vertexshader").c_str(), (name + ".fragmentshader").c_str());
	
	M = glGetUniformLocation(program, "M");
	V = glGetUniformLocation(program, "V");
	P = glGetUniformLocation(program, "P");

	if (isObject) {
		objectID = glGetUniformLocation(program, "objectID");
	}
	else {
		objectID = NULL;
	}

	La = glGetUniformLocation(program, "light.La");
	Ld = glGetUniformLocation(program, "light.Ld");
	Ls = glGetUniformLocation(program, "light.Ls");
	lightPosition = glGetUniformLocation(program, "light.lightPosition_worldspace");
	lightPower = glGetUniformLocation(program, "light.power");

	textureAtlas = glGetUniformLocation(program, "textureAtlasSampler");
}