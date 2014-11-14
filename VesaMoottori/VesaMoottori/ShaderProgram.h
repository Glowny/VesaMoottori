#pragma once
#include "GL\glew.h"
#include <string>
#include <map>
#include <iostream>

// ShaderProgram sis‰lt‰‰ shader objektin jota muokataan ja johon voi lis‰t‰ shadereita.
// Shader objekti alustetaan vasta kun ensimm‰inen shader-ohjelma lis‰t‰‰n siihen.

// [CreateShader]				Luo shadereita valmiiksi tehdyist‰ (.txt) filuista ja kiinnitt‰‰ ne suoraan johonkin ohjelmaan.
// [LinkProgram] [RunProgram]	Linkataan ja k‰ynnistet‰‰n ohjelma milloin halutaan. 
// [GetProgram]					Palauttaa ohjelman sijainnin.

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram() {};

	bool AddShader(char* shaderCode, GLenum type);
	bool LinkProgram();

	void RunProgram() {
		glUseProgram(glObject);
	}

	int GetProgramLocation(std::string programName) {
		return glObject;
	}

	int GetAttributeLocation(std::string attributeName) {
		GLuint tempLocation = glGetAttribLocation(glObject, attributeName.c_str());
		std::cout << "Searching for " << attributeName << ", location is: " << tempLocation << std::endl;
		return tempLocation;
	}

	bool GetLinkStatus() {
		GLint isLinked = 0;
		glGetProgramiv(glObject, GL_LINK_STATUS, (int*)&isLinked);

		if (isLinked == GL_FALSE)
			return false;

		else
			return true;
	}

	void GetAttribPointer(GLuint pos, GLuint color, GLuint tex);

private:
	GLuint glObject;
	bool created;
};