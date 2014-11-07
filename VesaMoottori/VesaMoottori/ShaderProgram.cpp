#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
//#define NDEBUG	// poista kommentointi t�st� niin assertit poistetaan k�yt�st�.
#include <cassert>
ShaderProgram::ShaderProgram()
{
	created = false;
	glObject = 0;
}

bool ShaderProgram::AddShader(char* shaderCode, GLenum type)
{
	if(!created)
	{
		glObject = glCreateProgram();
		created = true;
	}

	GLuint newShader = glCreateShader(type); // Luodaan tyhj� shaderi.
	GLint linkCheck = NULL;

	/*char *code = resourceManager.ShaderReader(textFile); // Luetaan koodi ennalta luetusta .txt filusta.
	if (shaderCode == NULL) // Tarkistetaan onnistuiko lukeminen.
	{
		std::cout << "Ongelmia " << textFile << " lukemisesssa." << std::endl;
		return false;
	}*/

	glShaderSource(newShader, 1, &shaderCode, NULL); // Lis�t��n shaderin koodi itse shaderiin.
	glCompileShader(newShader); // Kompiloidaan shadereiden koodit.

	glGetShaderiv(newShader, GL_COMPILE_STATUS, &linkCheck); // Testataan onnistuiko kompilointi.
	std::cout << "AddShader type (" << type << ") compile: " << linkCheck << std::endl;
	assert(linkCheck);	// pistin kaatumaan jos failaa, koska atm miss��n ei checkata t�m�n funktion palauttamaa boolia.
	if (linkCheck == 0)
		return false;

	glAttachShader(glObject, newShader); // Lis�t��n shaderit shader-ohjelmaan.
	return true;
};

bool ShaderProgram::LinkProgram()
{
	GLint linkCheck = NULL;
	glLinkProgram(glObject); // Linkkaaminen luo executablen shadereihin, jotka siihen on lis�tty.
	glGetProgramiv(glObject, GL_LINK_STATUS, &linkCheck); // Testatataan shadereiden linkkaaminen objektiin.
	std::cout << "Program [" << glObject << "] linker bool: " << linkCheck << std::endl;
	assert(linkCheck); // Kaatumaan jos failaa, koska t�m�n palauttamaa boolia ei checkata atm.
	if (linkCheck == 0)
		return false;
	else
		return true;
}