#pragma once
#include "GL\glew.h"
#include "ShaderVertexAttrib.h"
#include <string>
#include <map>
#include <iostream>
#include <vector>

// ShaderProgram sis‰lt‰‰ shader objektin jota muokataan ja johon voi lis‰t‰ shadereita.
// Shader objekti alustetaan vasta kun ensimm‰inen shader-ohjelma lis‰t‰‰n siihen.

// [CreateShader]				Luo shadereita valmiiksi tehdyist‰ (.txt) filuista ja kiinnitt‰‰ ne suoraan johonkin ohjelmaan.
// [LinkProgram] [RunProgram]	Linkataan ja k‰ynnistet‰‰n ohjelma milloin halutaan. 
// [GetProgram]					Palauttaa ohjelman sijainnin.

class ShaderProgram
{
public:
	ShaderProgram() : created(false), glObject(0) {};
	~ShaderProgram() {};

	bool AddShader(char* shaderCode, GLenum type);
	void AddVertexAttribPointer(std::string attributeName, GLint size, GLsizei stride, GLint offset);
	bool LinkProgram();
	void RunProgram();

	int GetAttributeLocation(std::string attributeName);
	int GetProgramLocation(std::string programName);
	bool GetLinkStatus();

	//void GetAttribPointer(GLuint pos, GLuint color, GLuint tex);

private:
	std::vector<ShaderVertexAttrib> vertexAttribs;
	GLuint glObject;
	bool created;
};