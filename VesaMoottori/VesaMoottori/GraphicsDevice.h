#pragma once
#include "Window.h"

class GraphicsDevice
{
public:
	GraphicsDevice() {
		renderingContext	= 0;
		pixelFormat			= 0;
	}

	GraphicsDevice(std::string name, int width, int height) {
		window				= Window(name, width, height);
		renderingContext	= 0;
		pixelFormat			= 0;
	}

	bool IsOpen();
	bool Close();
	bool Register();
	void Update();
	void Show();
	void Clear();
	bool Glew(); // Voisi muokata testaamaan muita GL-versioita.
	vector2i GetWindowSize(); //Palauttaa X ja Y koot ikkunasta.
	~GraphicsDevice() {};

private:
	Window					window;
	HGLRC					renderingContext; // OpenGL rendering context.
	PIXELFORMATDESCRIPTOR	winPixel; // Describes the pixel format of a drawing surface.
	int						pixelFormat;
};

//wglDeleteContext(hGLRC); // Tuhotaan renderöinti sisältö - pitää vielä koodata windowiin.