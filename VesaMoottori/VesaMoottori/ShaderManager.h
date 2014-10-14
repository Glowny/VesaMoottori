#pragma once
#include "GL\glew.h"
#include <string>
#include <map>
		
	// [CreateProgram]				K‰ytt‰j‰ luo tyhj‰n ohjelman ja antaa sille nimen.
	// [CreateShader]				Luo shadereita valmiiksi tehdyist‰ (.txt) filuista ja kiinnitt‰‰ ne suoraan johonkin ohjelmaan.
	// [LinkProgram] [RunProgram]	Linkataan ja k‰ynnistet‰‰n ohjelma milloin halutaan. 
	// [GetProgram]					Palauttaa ohjelman sijainnin.
	
class ShaderManager
{
public:
	ShaderManager() {};
	~ShaderManager() {};

	bool CreateShader(std::string shaderName, std::string targetProgram, GLenum type);
	void CreateProgram(std::string programName);
	bool LinkProgram(std::string programName);

	void RunProgram(std::string programName) {
		glUseProgram(Shaders[programName]);
	}

	int GetProgramLocation(std::string programName) {
		return Shaders[programName];
	}

	int GetAttributeLocation(std::string programName, std::string attributeName) {
		return glGetAttribLocation(Shaders[programName], attributeName.c_str());
	}

private:
	char *ShaderReader(std::string fileName);
	std::map <std::string, GLuint> Shaders;
};
