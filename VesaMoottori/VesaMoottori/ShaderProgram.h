#pragma once
#include "GL\glew.h"
#include <string>
#include <map>
#include <iostream>
		
	// [CreateProgram]				K‰ytt‰j‰ luo tyhj‰n ohjelman ja antaa sille nimen.
	// [CreateShader]				Luo shadereita valmiiksi tehdyist‰ (.txt) filuista ja kiinnitt‰‰ ne suoraan johonkin ohjelmaan.
	// [LinkProgram] [RunProgram]	Linkataan ja k‰ynnistet‰‰n ohjelma milloin halutaan. 
	// [GetProgram]					Palauttaa ohjelman sijainnin.
	
class ShaderProgram
{
public:
	ShaderProgram();
	//ShaderProgram(){ glObject = glCreateProgram(); }
	~ShaderProgram() {};

	bool CreateShader(std::string shaderName, GLenum type);
	bool LinkProgram();

	void RunProgram(std::string programName) {
		glUseProgram(Shaders[programName]);
	}

	int GetProgramLocation(std::string programName) {
		return Shaders[programName];
	}

	int GetAttributeLocation(std::string attributeName) {
		GLuint tempLocation = glGetAttribLocation(glObject, attributeName.c_str());
		std::cout << "Searching for " << attributeName << ", location is: " << tempLocation << std::endl;
		return tempLocation;
	}
	

private:
	char *ShaderReader(std::string fileName);
	std::map <std::string, GLuint> Shaders;
	GLuint glObject;
	bool created;
};

