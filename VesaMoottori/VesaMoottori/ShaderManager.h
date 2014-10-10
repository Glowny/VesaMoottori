#pragma once
#include <iostream>
#include "GL\glew.h"
#include <vector>
#include <map>


class ShaderManager
{
public:
	ShaderManager(){};
	void CreateShader(std::string shaderName, std::string fileName, GLenum type);
	void CreateProgram(std::string shaderName);
	~ShaderManager() {};
	void TestShaders();
	void Run(std::string shaderName);
	int GetObjects(std::string programName);


private:

	char *ShaderReader(std::string fileName);

	std::map <std::string, GLuint> Shaders;
};
