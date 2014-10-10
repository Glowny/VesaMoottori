#pragma once
#include "Window.h"

class GraphicsDevice
{
public:
	GraphicsDevice() {
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
	//HWND					hWindow; // Window handle talteen.
	//HDC					hDC; // Otetaan window device context talteen.
	Window					window;
	HGLRC					renderingContext; // OpenGL rendering context.
	PIXELFORMATDESCRIPTOR	winPixel; // Describes the pixel format of a drawing surface.
	int						pixelFormat;
};