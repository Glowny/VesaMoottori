#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include "ShaderManager.h"
#include "Window.h"
#include "ResourceManager.h"

static const GLfloat triangleData[] =
{
	-0.5f, 0.5f,
	1.0f, 0.0f, 0.0f,

	0.5f, -0.5f,
	0.0f, 1.0f, 0.0f,

	0.5f, 0.5f,
	0.0f, 0.0f, 1.0f
};

static const GLuint indexData[] = { 0, 1, 2 };

int main()
{
	bool			isRunning = true;
	MSG				messages;
	Window			pekka;
	ShaderManager	shaders;
	ResourceManager ressu;

	pekka.Register();
	pekka.Show();
	shaders.TestShaders();
	ressu.loadImage("tex.png");


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


	// Tekstuurien luonti:
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 130, 131, 0, GL_RGB, GL_BITMAP, ressu.findImage("tex.png"));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0u);


	// Tarkistetaan attribuuttien lokaatio.
	const GLint posLocation = glGetAttribLocation(shaders.GetObjects(), "attrPosition");
	std::cout << "Attribute index: " << posLocation << std::endl;
	glEnableVertexAttribArray(posLocation);

	const GLint colorLocation = glGetAttribLocation(shaders.GetObjects(), "attrColor");
	std::cout << "Color index: " << colorLocation << std::endl;
	glEnableVertexAttribArray(colorLocation);


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
			//glClear(GL_COLOR_BUFFER_BIT);
			pekka.Update();
			shaders.Run(); // Lisätään shader-ohjelma tämänhetkiseen renderöintiin.

			// Vaihtoehto kolmion piirrolle:
			glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
			glVertexAttribPointer(posLocation, 2, GL_FLOAT, GL_FALSE, 20u, reinterpret_cast<GLvoid*>(0));
			glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 20u, reinterpret_cast<GLvoid*>(8));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
			glDrawElements(GL_TRIANGLES, 3u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
			glBindBuffer(GL_ARRAY_BUFFER, 0u);
			glUseProgram(0);
			//SwapBuffers(hDC); // Swapataan buffereita piirtoa varten.
		}
	}

	//glDeleteTextures(1, &texture);
	glDeleteBuffers(2, buffers);
	return (int) messages.wParam;
}