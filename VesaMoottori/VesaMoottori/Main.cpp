#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include "GraphicsDevice.h"
#include "ResourceManager.h"
#include "TextureManager.h"
#include "GL\glew.h"
#include "Buffers.h"
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
	TextureManager textureManager;
	bool			isRunning = true;
	MSG				messages;
	GraphicsDevice	pekka;
	Buffers			buffer;
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


	// Lis‰t‰‰n shaderin koodi itse shaderiin.
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

	// Lis‰t‰‰n shaderit shader-ohjelmaan.
	glAttachShader(glObject, glVertexShader);
	glAttachShader(glObject, glFragmentShader);
	glLinkProgram(glObject); // Linkkaaminen luo executablen shadereihin, jotka siihen on lis‰tty.
	glGetProgramiv(glObject, GL_LINK_STATUS, &linkCheck); // Testatataan shadereiden linkkaaminen objektiin.
	std::cout << "Linker bool: " << linkCheck << std::endl;


	// Buffereiden luonti
	GLuint vertexBuffer = buffer.CreateBuffers(GL_ARRAY_BUFFER, triangleData, sizeof(triangleData));
	GLuint indexBuffer = buffer.CreateBuffers(GL_ELEMENT_ARRAY_BUFFER, indexData, sizeof(indexData));

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	resourceManager.RLoadImage("goofy.png");
	ImageInfo *image= resourceManager.FindImage("goofy.png");
	GLuint texture = textureManager.CreateTexture(*image);

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
		while (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE)) // Main loop jossa ikkuna ottaa vastaan viestej‰.
		{
			if (messages.message == WM_QUIT)
			{
				isRunning = false;
				//wglDeleteContext(hGLRC); // Tuhotaan renderˆinti sis‰ltˆ.
				break;
			}
			DispatchMessage(&messages);
			pekka.Update();
			//shaders.Run(); // Lis‰t‰‰n shader-ohjelma t‰m‰nhetkiseen renderˆintiin.
			glUseProgram(glObject);

			// Vaihtoehto kolmion piirrolle:
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			// kai n‰‰kin saa jotenni shader- ja texturemanagerille tai jollekkin, joka vahtii kumpaakin.
			glVertexAttribPointer(posLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
			glVertexAttribPointer(colorLocation, 3u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
			glVertexAttribPointer(texLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(5 * sizeof(GLfloat)));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
			glBindTexture(GL_TEXTURE_2D, texture);
			glDrawElements(GL_TRIANGLES, 3u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));
			glBindTexture(GL_TEXTURE_2D, 0u);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
			glBindBuffer(GL_ARRAY_BUFFER, 0u);

			glUseProgram(0);
		}
	}
	glDeleteTextures(1, &texture);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	return (int) messages.wParam;
}

