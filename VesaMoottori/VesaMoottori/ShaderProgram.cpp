#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <cassert>

bool ShaderProgram::AddShader(char* shaderCode, GLenum type)
{
	if(!created)
	{
		glObject = glCreateProgram();
		created = true;
	}

	GLuint newShader = glCreateShader(type); // Luodaan tyhj‰ shaderi.
	GLint linkCheck = NULL;

	glShaderSource(newShader, 1, &shaderCode, NULL); // Lis‰t‰‰n shaderin koodi itse shaderiin.
	glCompileShader(newShader); // Kompiloidaan shadereiden koodit.

	glGetShaderiv(newShader, GL_COMPILE_STATUS, &linkCheck); // Testataan onnistuiko kompilointi.
	std::cout << "AddShader type (" << type << ") compile: " << linkCheck << std::endl;
	assert(linkCheck != GL_FALSE);	
	if (linkCheck == 0)
		return false;

	glAttachShader(glObject, newShader); // Lis‰t‰‰n shaderit shader-ohjelmaan.
	return true;
}

void ShaderProgram::AddVertexAttribPointer(std::string attributeName, GLint size, GLsizei stride, GLint offset)
{
	ShaderVertexAttrib tempAttrib;
	tempAttrib.attributeName = attributeName;
	tempAttrib.offset = offset;
	tempAttrib.size = size;
	tempAttrib.stride = stride;
	vertexAttribs.push_back(tempAttrib);
}

bool ShaderProgram::LinkProgram()
{
	GLint linkCheck = NULL;
	glLinkProgram(glObject); // Linkkaaminen luo executablen shadereihin, jotka siihen on lis‰tty.
	glGetProgramiv(glObject, GL_LINK_STATUS, &linkCheck); // Testatataan shadereiden linkkaaminen objektiin.
	std::cout << "Program [" << glObject << "] linker bool: " << linkCheck << std::endl;
	assert(linkCheck != GL_FALSE); // Kaatumaan jos failaa, koska t‰m‰n palauttamaa boolia ei checkata atm.
	if (linkCheck == 0)
		return false;
	else
		return true;
}

void ShaderProgram::RunProgram()
{
	if(vertexAttribs.size() != 0)
	{
		for(std::vector<ShaderVertexAttrib>::iterator it = vertexAttribs.begin(); it != vertexAttribs.end(); it++)
		{
			GLint location = GetAttributeLocation(it->attributeName);
			glVertexAttribPointer(location, it->size, GL_FLOAT, GL_FALSE,
				it->stride * sizeof(GLfloat), reinterpret_cast<GLvoid*>((it->offset) * sizeof(GLfloat)));
			glEnableVertexAttribArray(location);
		}
	}
	glUseProgram(glObject);
}

int ShaderProgram::GetProgramLocation(std::string programName)
{
	return glObject;
}

int ShaderProgram::GetAttributeLocation(std::string attributeName)
{
	GLuint tempLocation = glGetAttribLocation(glObject, attributeName.c_str());
	//std::cout << "Searching for " << attributeName << ", location is: " << tempLocation << std::endl;
	return tempLocation;
}

bool ShaderProgram::GetLinkStatus()
{
	GLint* isLinked = new GLint;
	glGetProgramiv(glObject, GL_LINK_STATUS, isLinked);
	if(isLinked == GL_FALSE)
		return false;
	else
		return true;
}