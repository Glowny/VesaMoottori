#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include "Window.h"
#include "ResourceManager.h"
//#include "ShaderManager.h"

char* ShaderReader(std::string fileName);

static const GLfloat triangleData[] =
{
	-0.7f, -0.7f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f,

	0.0f, 0.7f,
	0.0f, 1.0f, 0.0f,
	0.5f, 1.0f,

	0.7f, -0.7f,
	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f
};

static const GLuint indexData[] = { 0, 1, 2 };
int main()
{
	ResourceManager resourceManager;
	bool			isRunning = true;
	MSG				messages;
	Window			pekka;
	//ShaderManager	shaders;
	//ResourceManager ressu;

	pekka.Register();
	pekka.Show();
	//shaders.TestShaders();
	//ressu.loadImage("tex.png");


	GLuint glObject = glCreateProgram(); // Represents compiled executable shader code.
	GLuint glVertexShader = glCreateShader(GL_VERTEX_SHADER); // Represents compiled shader code of a single shader stage.
	GLuint glFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint linkCheck = NULL; // Testaamista varten.
	char *vertexCode = resourceManager.LoadShader("vertexShader.txt"); // Shaderin koodi tekstitiedostosta.
	char *fragmentCode = resourceManager.LoadShader("fragmentShader.txt");


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


	// Vaihtoehtoinen kolmion piirto:
	GLuint buffers[2];
	glGenBuffers(2, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]); // Vertex datan puskuri.
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);


	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);


	std::vector<unsigned char> image;
	unsigned width, height;	// lodepng asettaa arvot
	const char* filename = "goofy.png";
	unsigned error = lodepng::decode(image, width, height, filename);
	std::cout << "loadImage: " << error << " : " << lodepng_error_text(error) << std::endl;


	// Tekstuurien luonti:
	glEnable(GL_TEXTURE_2D);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0u);


	// Tarkistetaan attribuuttien lokaatio.
	//const GLint posLocation = 0;
	//glBindAttribLocation(glObject, posLocation, "attrPosition");
	const GLint posLocation = glGetAttribLocation(glObject, "attrPosition");
	std::cout << "Position Attribute index: " << posLocation << std::endl;
	glEnableVertexAttribArray(posLocation);

	const GLint colorLocation = glGetAttribLocation(glObject, "attrColor");
	std::cout << "Color Attribute index: " << colorLocation << std::endl;
	//glBindAttribLocation(glObject, 1, "attrColor");
	//glEnableVertexAttribArray(colorLocation);

	const GLint texLocation = glGetAttribLocation(glObject, "textPosition");
	std::cout << "Position Texture index: " << texLocation << std::endl;
	//glBindAttribLocation(glObject, 2, "textPosition");
	glEnableVertexAttribArray(texLocation);


	while (isRunning) // Ohjelman main-looppi.
	{
		while (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE)) // Main loop jossa ikkuna ottaa vastaan viestejä.
		{
			if (messages.message == WM_QUIT)
			{
				isRunning = false;
				//wglDeleteContext(hGLRC); // Tuhotaan renderöinti sisältö.
				break;
			}
			DispatchMessage(&messages);
			pekka.Update();
			//shaders.Run(); // Lisätään shader-ohjelma tämänhetkiseen renderöintiin.
			glUseProgram(glObject);

			// Vaihtoehto kolmion piirrolle:
			glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
			glVertexAttribPointer(posLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
			glVertexAttribPointer(colorLocation, 3u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
			glVertexAttribPointer(texLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(5 * sizeof(GLfloat)));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
			glBindTexture(GL_TEXTURE_2D, texture);
			glDrawElements(GL_TRIANGLES, 3u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));
			glBindTexture(GL_TEXTURE_2D, 0u);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
			glBindBuffer(GL_ARRAY_BUFFER, 0u);

			glUseProgram(0);
		}
	}

	glDeleteTextures(1, &texture);
	glDeleteBuffers(2, buffers);
	return (int) messages.wParam;
}

char* ShaderReader(std::string fileName)
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