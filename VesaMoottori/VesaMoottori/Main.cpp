#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include "ShaderManager.h"
#include "Window.h"

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
	bool		isRunning = true;
	MSG			messages;
	Window		window;

	window.Register();
	window.Show();

	// Vaihtoehtoinen kolmion piirto:
	GLuint buffers[2];
	glGenBuffers(2, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]); // Vertex datan puskuri.
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	

	// Tekstuurien luonti:
	//gluint texture;
	//glgentextures(1, &texture);
	//glbindtexture(gl_texture_2d, texture);
	//glteximage2d(gl_texture_2d, 0, 4, <width>, <height>, 0, <format>, <type>, <data>);
	//gltexparameteri(gl_texture_2d, gl_texture_min_filter, gl_linear);
	//glbindtexture(gl_texture_2d, 0u);
	//Vertex shaderiin koordinaatit -> Fragment -> Texture Coords/Vertexiin -> BindTexture ennen piirtoa -> sampler yks. index


	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	// K‰yet‰‰n GLSL #version 120 tai aiempaa.
	// http://www.opengl.org/wiki/Shader_Compilation
	ShaderManager Shaders;
	Shaders.initialize();


	// Tarkistetaan attribuuttien lokaatio.
	const GLint posLocation = glGetAttribLocation(Shaders.GetObjects(), "attrPosition");
	std::cout << "Attribute index: " << posLocation << std::endl;
	glEnableVertexAttribArray(posLocation);

	const GLint colorLocation = glGetAttribLocation(Shaders.GetObjects(), "attrColor");
	std::cout << "Color index: " << colorLocation << std::endl;
	glEnableVertexAttribArray(colorLocation);


	while (isRunning) // Ohjelman main-looppi.
	{
		while (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE)) // Main loop jossa ikkuna ottaa vastaan viestej‰.
		{
			//TranslateMessage(&messages); // K‰‰nt‰‰ n‰pp‰in painalluksia tunnetuksi koodiksi.
			if (messages.message == WM_QUIT)
			{
				isRunning = false;
				//wglDeleteContext(hGLRC); // Tuhotaan renderˆinti sis‰ltˆ.
				break;
			}
			DispatchMessage(&messages);
			//glClear(GL_COLOR_BUFFER_BIT);
			window.Update();
			Shaders.run(); // Lis‰t‰‰n shader-ohjelma t‰m‰nhetkiseen renderˆintiin.

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