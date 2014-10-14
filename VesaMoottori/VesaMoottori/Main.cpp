#include "GraphicsDevice.h"
#include "ResourceManager.h"
#include "TextureManager.h"
#include "GL\glew.h"
#include "Buffers.h"
#include "ShaderManager.h"

static const GLfloat triangleData[] =
{
	-0.8f, -0.8f, // Positio.
	1.0f, 0.0f, 0.0f, // Väri.
	0.0f, 0.0f, // Tekstuuri.

	-0.8f, 0.8f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f,

	0.8f, 0.8f,
	0.0f, 0.0f, 1.0f,
	1.0f, 1.0f,

	0.8f, -0.8f,
	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f
};

static const GLuint indexData[] = { 0, 1, 2, 3 };

int main()
{
	ResourceManager resourceManager;
	TextureManager	textureManager;
	bool			isRunning = true;
	MSG				messages;
	GraphicsDevice	pekka("eitoimicustomnimi", 800, 800);
	Buffers			buffer;
	ShaderManager	shaders;

	pekka.Register();
	pekka.Show();

	shaders.CreateProgram("saku");
	shaders.CreateShader("vertexShader.txt", "saku", GL_VERTEX_SHADER);
	shaders.CreateShader("fragmentShader.txt", "saku", GL_FRAGMENT_SHADER);
	shaders.LinkProgram("saku");


	// Buffereiden luonti
	GLuint vertexBuffer = buffer.CreateBuffers(GL_ARRAY_BUFFER, triangleData, sizeof(triangleData));
	GLuint indexBuffer = buffer.CreateBuffers(GL_ELEMENT_ARRAY_BUFFER, indexData, sizeof(indexData));

	glClearColor(0.0f, 0.8f, 0.0f, 0.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	resourceManager.RLoadImage("goofy.png");
	ImageInfo *image= resourceManager.FindImage("goofy.png");
	GLuint texture = textureManager.CreateTexture(*image);
	//GLuint texture = resourceManager.FindImage("goofy.png");


	// Tarkistetaan attribuuttien lokaatio.
	const GLint posLocation = shaders.GetAttributeLocation("saku", "attrPosition");
	const GLint colorLocation = shaders.GetAttributeLocation("saku", "attrColor");
	const GLint texLocation = shaders.GetAttributeLocation("saku", "textPosition");


	while (isRunning)
	{
		while (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE)) // Ikkuna ottaa vastaan viestejä.
		{
			if (messages.message == WM_QUIT)
			{
				isRunning = false;
				//wglDeleteContext(hGLRC); // Tuhotaan renderöinti sisältö - pitää vielä koodata windowiin.
				break;
			}

			DispatchMessage(&messages);
			pekka.Update();
			shaders.RunProgram("saku");
			glClear(GL_COLOR_BUFFER_BIT);

			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glVertexAttribPointer(posLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
			glVertexAttribPointer(colorLocation, 3u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
			glVertexAttribPointer(texLocation, 2u, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(5 * sizeof(GLfloat)));

			glEnableVertexAttribArray(posLocation);
			glEnableVertexAttribArray(colorLocation);
			glEnableVertexAttribArray(texLocation);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
			glBindTexture(GL_TEXTURE_2D, texture);
			glDrawElements(GL_QUADS, 4u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));

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