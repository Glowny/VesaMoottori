#pragma once
#include <iostream>
#include "GL\glew.h"

class ShaderManager
{
public:
	ShaderManager() {};
	~ShaderManager() {};
	void TestShaders();
	void Run();
	int GetObjects();

private:
	char *ShaderReader(std::string fileName);
	GLuint	glObject;

	//GLuint	glVertexShader;
	//GLuint	glFragmentShader;
	//GLint		linkCheck;
	//char		*vertexCode;
	//char		*fragmentCode;
};
