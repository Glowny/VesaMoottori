#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <cassert>
//#define NDEBUG // Poista kommentointi t�st� niin assertit poistetaan k�yt�st�.
// Voi my�s laittaa preprocessor macroihin.

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

void ShaderProgram::GetAttribPointer(GLuint pos,GLuint color, GLuint tex)
{
	glVertexAttribPointer(pos, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat),
		reinterpret_cast<GLvoid*>(0));
	glVertexAttribPointer(color, 3u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat),
		reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
	glVertexAttribPointer(tex, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat),
		reinterpret_cast<GLvoid*>(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(pos);
	glEnableVertexAttribArray(color);
	glEnableVertexAttribArray(tex);
}

void ShaderProgram::RunProgram()
{
	glUseProgram(glObject);
}

int ShaderProgram::GetProgramLocation(std::string programName)
{
	return glObject;
}