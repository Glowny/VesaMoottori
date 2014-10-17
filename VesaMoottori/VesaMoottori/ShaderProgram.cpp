#include "ShaderProgram.h"
#include <iostream>
#include <fstream>

ShaderProgram::ShaderProgram()
{
	created = false;
	glObject = 0;
	// Luodaan uusi glProgram.
	//Shaders.insert(std::make_pair(programName, glObject));	// Ja tungetaan se mappiin nimellä.
	//HUOM: Jos tehdää CreateProgram funktio niin nämä sinne ^
}

bool ShaderProgram::CreateShader(std::string shaderName, GLenum type)
{
	if(!created)
	{
		glObject = glCreateProgram();
		created = true;
	}

	GLuint newShader = glCreateShader(type); // Luodaan tyhjä shaderi.
	GLint linkCheck = NULL;

	char *code = ShaderReader(shaderName); // Luetaan koodi ennalta luetusta .txt filusta.
	if (code == NULL) // Tarkistetaan onnistuiko lukeminen.
	{
		std::cout << "Ongelmia " << shaderName << " lukemisesssa." << std::endl;
		return false;
	}

	glShaderSource(newShader, 1, &code, NULL); // Lisätään shaderin koodi itse shaderiin.
	glCompileShader(newShader); // Kompiloidaan shadereiden koodit.

	glGetShaderiv(newShader, GL_COMPILE_STATUS, &linkCheck); // Testataan onnistuiko kompilointi.
	std::cout << shaderName << " compile: " << linkCheck << std::endl;
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
	std::cout << glObject << " linker bool: " << linkCheck << std::endl;
	if (linkCheck == 0)
		return false;
	else
		return true;
}

char* ShaderProgram::ShaderReader(std::string fileName)
{
	// Avataan luettava tiedosto ja tarkistetaan onnistuminen.
	std::ifstream readFile(fileName, std::ios::in);
	if (readFile.is_open())
		std::cout << "Opening file: " << fileName << std::endl;
	else
	{
		std::cout << "Could not open file: " << fileName << std::endl;
		return NULL;
	}

	// Luettavan tiedoston pituus.
	readFile.seekg(0, readFile.end); // Pistetään char position filun loppuun.
	int fileLength = (int)readFile.tellg(); // Pistetään pituus ylös.
	readFile.seekg(0, readFile.beg); // Positio takasin alkuun.
	if (fileLength == 0)
	{
		std::cout << "ERROR: Luettavan tiedoston pituus 0." << std::endl;
		return NULL;
	}
	else
		std::cout << "Luettavan tiedoston pituus: " << fileLength << std::endl;

	std::string fileContents((std::istreambuf_iterator<char>(readFile)),
		std::istreambuf_iterator<char>()); // Kopioidaan tiedoston sisältö stringiin.
	char *tempChar = new char[fileContents.length() + 1];
	std::strcpy(tempChar, fileContents.c_str()); // Kopioidaan tiedoston sisällöt dynaamisesti luotuun char-merkkijonoon.

	std::cout << "Closing file: " << fileName << std::endl;
	readFile.close();

	return tempChar;
}