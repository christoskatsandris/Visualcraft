#include "program.h"
#include "shader.h"
#include <string>

using namespace std;

BaseProgram::BaseProgram(string name) {
	program = loadShaders((name + ".vertexshader").c_str(), (name + ".fragmentshader").c_str());
}

Program::Program(string name)
	: BaseProgram(name)
{
	M = glGetUniformLocation(program, "M");
	V = glGetUniformLocation(program, "V");
	P = glGetUniformLocation(program, "P");

	objectID = glGetUniformLocation(program, "objectID");
	rayCastedID = glGetUniformLocation(program, "rayCastedID");
}

DepthProgram::DepthProgram(string name)
	: Program(name) 
{

}

LightProgram::LightProgram(string name)
	: Program(name)
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