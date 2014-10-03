#pragma once
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <cassert>

#include <GL\glew.h>
#include <GL\GLU.h>
#include <GL\GL.h>

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();
	void initialize();
	void run();
	int GetObjects();

private:
	char *ShaderReader(std::string fileName);



	GLuint glObject;
	GLuint glVertexShader;
	GLuint glFragmentShader;
	GLint linkCheck = NULL;
	char *vertexCode;
	char *fragmentCode;

};
