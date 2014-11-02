#include "ShaderProgram.h"
#include <iostream>
#include <fstream>

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

	GLuint newShader = glCreateShader(type); // Luodaan tyhjä shaderi.
	GLint linkCheck = NULL;

	/*char *code = resourceManager.ShaderReader(textFile); // Luetaan koodi ennalta luetusta .txt filusta.
	if (shaderCode == NULL) // Tarkistetaan onnistuiko lukeminen.
	{
		std::cout << "Ongelmia " << textFile << " lukemisesssa." << std::endl;
		return false;
	}*/

	glShaderSource(newShader, 1, &shaderCode, NULL); // Lisätään shaderin koodi itse shaderiin.
	glCompileShader(newShader); // Kompiloidaan shadereiden koodit.

	glGetShaderiv(newShader, GL_COMPILE_STATUS, &linkCheck); // Testataan onnistuiko kompilointi.
	std::cout << type << " compile: " << linkCheck << std::endl;
	if (linkCheck == 0)
		return false;

	glAttachShader(glObject, newShader); // Lisätään shaderit shader-ohjelmaan.
	return true;
};

bool ShaderProgram::LinkProgram()
{
	GLint linkCheck = NULL;
	glLinkProgram(glObject); // Linkkaaminen luo executablen shadereihin, jotka siihen on lisätty.
	glGetProgramiv(glObject, GL_LINK_STATUS, &linkCheck); // Testatataan shadereiden linkkaaminen objektiin.
	std::cout << "Program [" << glObject << "] linker bool: " << linkCheck << std::endl;
	if (linkCheck == 0)
		return false;
	else
		return true;
}