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

	bool Register();
	bool Glew(); // Voisi muokata testaamaan muita GL-versioita.

	 void Show() {
		ShowWindow(window.GetHandle(), SW_SHOWNORMAL);
	}

	void Update() {
		UpdateWindow(window.GetHandle());
		SwapBuffers(window.GetDevice());
	} 

	~GraphicsDevice() {};

private:
	Window					window;
	HGLRC					renderingContext; // OpenGL rendering context.
	PIXELFORMATDESCRIPTOR	winPixel; // Describes the pixel format of a drawing surface.
	int						pixelFormat;
};