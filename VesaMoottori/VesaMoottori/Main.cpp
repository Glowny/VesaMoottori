#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <cassert>

#include "ShaderManager.h"

#include <GL\glew.h>
#include <GL\GLU.h>
#include <GL\GL.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
bool GlewTests(); // Palauttaa true jos glew testit onnistuu.

//static const GLfloat triangleData[] = // Vertex koordinaatit kolmion piirtoon.
//{ 
//	-0.7f,	-0.6f,	0.1f,
//	0.7f,	-0.5f,	0.2f,
//	0.1f,	 0.2f,	0.0f,
//};

static const GLfloat triangleData[] = // V‰ritetty versio.
{
	-0.5f, 0.5f,
	1.0f, 0.0f, 0.0f,

	0.5f, -0.5f,
	0.0f, 1.0f, 0.0f,

	0.5f, 0.5f,
	0.0f, 0.0f, 1.0f
};

static const GLuint indexData[] = { 0, 1, 2 };

//GLint FileLength(); // Tarkastetaan .txt tiedoston pituus.
//bool InitGL(GLvoid); // Alustetaan OpenGL.
//bool DrawGLScene(GLvoid); // Alustetaan ikkuna piirt‰mist‰ varten.
//bool CreateGLWindow();
//GLvoid CloseGLWindow(GLvoid); // Vapauttaa asioita kun ohjelma suljetaan.

int main()
{
	const TCHAR				winName[] = TEXT("Window");
	const TCHAR				winClassName[] = TEXT("Window");
	MSG						messages;
	HGLRC					hRC = NULL; // Permanent rendering context.
	HDC						hDC = NULL; // Private GDI device context.
	HGLRC					hGLRC = NULL; // OpenGL rendering context.
	HWND					winHandle = NULL; // Holds window handle.
	HINSTANCE				hInstance = GetModuleHandle(nullptr); // Instance of the application
	WNDCLASSEX				winClass; // Sis‰lt‰‰ ikkunan asetukset.
	PIXELFORMATDESCRIPTOR	winPixel; // Describes the pixel format of a drawing surface.
	bool					isRunning = true;
	int						pixFormat = NULL;

	// Alustetaan windows-ikkkuna.
	winClass.lpfnWndProc	= WndProc;
	winClass.cbSize			= sizeof(WNDCLASSEX);
	winClass.style			= CS_OWNDC;
	winClass.hInstance		= hInstance;
	winClass.hbrBackground	= CreateSolidBrush(RGB(255, 102, 255));
	winClass.lpszClassName	= winClassName;
	winClass.cbClsExtra		= NULL;
	winClass.cbWndExtra		= NULL;
	winClass.hIcon			= NULL;
	winClass.hCursor		= NULL;
	winClass.lpszMenuName	= NULL;
	winClass.hIconSm		= NULL;

	if (!RegisterClassEx(&winClass)) // Rekisterˆid‰‰n ikkuna ja tarkistetaan onnistuuko se.
		std::cout << "RegisterClassEx failed!" << std::endl;
	else
		std::cout << "RegisterClassEx succeeded!" << std::endl;

	winHandle = CreateWindowEx( // Luodaan ikkuna ja sille handle jonka kautta sit‰ voidaan k‰ytt‰‰.
		NULL,
		winName,
		winClassName,
		WS_OVERLAPPEDWINDOW,
		200, 200,
		500, 500,
		NULL, NULL,
		hInstance,
		NULL);

	if (!winHandle) // Tarkastetaan handlen luominen.
		std::cout << "WindowHandle failed!" << std::endl;
	else
		std::cout << "WindowHandle succeeded!" << std::endl;

	hDC = GetDC(winHandle); // Asetetaan arvo aiemmin alustetulle device contextille.

	// Alustetaan OpenGL varten.
	winPixel.nSize			= sizeof(PIXELFORMATDESCRIPTOR);
	winPixel.nVersion		= 1;
	winPixel.dwFlags		= PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | LPD_SUPPORT_OPENGL;
	winPixel.iPixelType		= PFD_TYPE_RGBA;
	winPixel.cColorBits		= 24;
	winPixel.cDepthBits		= 24;

	pixFormat = ChoosePixelFormat(hDC, &winPixel); // Etsit‰‰n l‰hin pixeliformaatti jota voidaan k‰ytt‰‰.
	if (!SetPixelFormat(hDC, pixFormat, &winPixel))
		std::cout << "SetPixelFormat failed!" << std::endl;
	else
		std::cout << "SetPixelFormat succeeded!" << std::endl;

	hGLRC = wglCreateContext(hDC); // Luodaan handle OpenGL renderˆinti‰ varten.
	wglMakeCurrent(hDC, hGLRC); // K‰ytet‰‰n t‰t‰ ikkunaa komentokutsuissa.

	ShowWindow(winHandle, SW_SHOWNORMAL); // N‰ytet‰‰n rekisterˆity ikkuna.
	UpdateWindow(winHandle);
	GlewTests(); // Testaa OpenGL 2.1 toimivuutta.


	// Piirrett‰‰n simppeli kolmio. Vertex attribute array sis‰lt‰‰ datan verticeist‰ mit‰ piirrett‰‰n.
	//GLuint vertexID;
	//glGenVertexArrays(1, &vertexID);
	//glBindVertexArray(vertexID);

	//GLuint vertexBuffer;
	//glGenBuffers(1, &vertexBuffer); // Luodaan yksi buffer objekti.
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // Bindataan bufferi vertex data targettiin.
	//glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW); // Luo ja alustaa bufferin sis‰llˆn.

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

	glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
	// K‰yet‰‰n GLSL #version 120 tai aiempaa.
	// http://www.opengl.org/wiki/Shader_Compilation

	ShaderManager Shaders;
	Shaders.initialize();

	// Tarkistetaan attribuuttien lokaatio.
	//GLint triangleLocation = glGetAttribLocation(glObject, "triangleData");
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
				wglDeleteContext(hGLRC); // Tuhotaan renderˆinti sis‰ltˆ.
				break;
			}
			DispatchMessage(&messages);
			glClear(GL_COLOR_BUFFER_BIT);
			Shaders.run(); // Lis‰t‰‰n shader-ohjelma t‰m‰nhetkiseen renderˆintiin.

			// Kolmion piirtoa varten.
			//glEnableVertexAttribArray(0); // Enable or disable a generic vertex attribute array.
			//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // Bindataan meid‰n bufferi kohteeseen.
			//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			//glDrawArrays(GL_TRIANGLES, 0, 3); // Render primitives from array data.
			//glDisableVertexAttribArray(0);

			// Vaihtoehto kolmion piirrolle:
			glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
			glVertexAttribPointer(posLocation, 2, GL_FLOAT, GL_FALSE, 20u, reinterpret_cast<GLvoid*>(0));
			glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 20u, reinterpret_cast<GLvoid*>(8));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
			glDrawElements(GL_TRIANGLES, 3u, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
			glBindBuffer(GL_ARRAY_BUFFER, 0u);
			glUseProgram(0);
			SwapBuffers(hDC); // Swapataan buffereita piirtoa varten.
		}
	}

	//glDeleteTextures(1, &texture);
	glDeleteBuffers(2, buffers);
	return (int) messages.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // Prosessoi viestej‰ ikkunalle.
{ 
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam); 
		break;
	}
	return 0;
} 

 bool GlewTests()
{
	GLenum error = glewInit(); // Alustetaan Glew.
	if (error == GLEW_OK)
		std::cout << "GLEW succeeded!" << std::endl;
	else
	{
		std::cout << "GLEW failed, error message: " << glewGetErrorString(error) << std::endl;
		return false;
	}

	if (GLEW_VERSION_2_1) // Tarkastetaan onko 2.1 k‰ytˆss‰.
		std::cout << "OpenGL 2.1 supported." << std::endl;
	else
	{
		std::cout << "OpenGL 2.1 not supported." << std::endl;
		return false;
	}
	return true;


}