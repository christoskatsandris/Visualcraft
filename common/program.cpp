#include "program.h"
#include "shader.h"
#include <string>

using namespace std;

BaseProgram::BaseProgram(string name) {
	program = loadShaders((name + ".vertexshader").c_str(), (name + ".fragmentshader").c_str());
}

Program::Program(string name, bool isObject)
	: BaseProgram(name)
{
	M = glGetUniformLocation(program, "M");
	V = glGetUniformLocation(program, "V");
	P = glGetUniformLocation(program, "P");

	if (isObject) {
		objectID = glGetUniformLocation(program, "objectID");
	}
	else {
		objectID = NULL;
	}
}

DepthProgram::DepthProgram(string name, bool isObject)
	: Program(name, isObject) 
{

}

LightProgram::LightProgram(string name, bool isObject)
	: Program(name, isObject)
{
	La = glGetUniformLocation(program, "light.La");
	Ld = glGetUniformLocation(program, "light.Ld");
	Ls = glGetUniformLocation(program, "light.Ls");
	lightPosition = glGetUniformLocation(program, "light.lightPosition_worldspace");
	lightPower = glGetUniformLocation(program, "light.power");

	textureAtlas = glGetUniformLocation(program, "textureAtlasSampler");

	lightVP = glGetUniformLocation(program, "lightVP");
	depthMap = glGetUniformLocation(program, "shadowMapSampler");
}

DepthMapProgram::DepthMapProgram(string name)
	: BaseProgram(name)
{
	texture = glGetUniformLocation(program, "textureSampler");
}