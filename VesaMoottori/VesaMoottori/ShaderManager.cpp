#include "ShaderManager.h"


ShaderManager::ShaderManager()
{}

ShaderManager::~ShaderManager()
{}


void ShaderManager::initialize()
{
	glObject = glCreateProgram(); // Represents compiled executable shader code.
	glVertexShader = glCreateShader(GL_VERTEX_SHADER); // Represents compiled shader code of a single shader stage.
	glFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	linkCheck = NULL; // Testaamista varten.
	vertexCode = ShaderReader("vertexShader.txt"); // Shaderin koodi tekstitiedostosta.
	fragmentCode = ShaderReader("fragmentShader.txt");

	// Lisätään shaderin koodi itse shaderiin.
	glShaderSource(glVertexShader, 1, &vertexCode, NULL);
	glShaderSource(glFragmentShader, 1, &fragmentCode, NULL);

	// Kompiloidaan shadereiden koodit.
	glCompileShader(glVertexShader);
	glCompileShader(glFragmentShader);

	// Testataan onnistuiko kompilointi.
	glGetShaderiv(glVertexShader, GL_COMPILE_STATUS, &linkCheck);
	std::cout << "Vertex shader compile: " << linkCheck << std::endl;
	glGetShaderiv(glFragmentShader, GL_COMPILE_STATUS, &linkCheck);
	std::cout << "Fragment shader compile: " << linkCheck << std::endl;

	// Lisätään shaderit shader-ohjelmaan.
	glAttachShader(glObject, glVertexShader);
	glAttachShader(glObject, glFragmentShader);
	glLinkProgram(glObject); // Linkkaaminen luo executablen shadereihin, jotka siihen on lisätty.
	glGetProgramiv(glObject, GL_LINK_STATUS, &linkCheck); // Testatataan shadereiden linkkaaminen objektiin.
	std::cout << "Linker bool: " << linkCheck << std::endl;
}

void ShaderManager::run()
{
	glUseProgram(glObject);
}

char* ShaderManager::ShaderReader(std::string fileName)
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

int ShaderManager::GetObjects()
{
	return glObject;
}