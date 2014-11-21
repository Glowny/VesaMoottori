#pragma once
#include "Window.h"

class GraphicsDevice
{
public:
	GraphicsDevice();
	GraphicsDevice(std::string name, int width, int height);
	~GraphicsDevice() {};

	void SetWindow(Window &window);

	bool IsOpen();
	bool Close();
	bool Register();
	void Update();
	void Show();
	void Clear();
	bool Glew(); // Voisi muokata testaamaan muita GL-versioita.
	vector2i GetWindowSize(); //Palauttaa X ja Y koot ikkunasta.

private:
	Window*					window;
	HGLRC					renderingContext; // OpenGL rendering context.
	PIXELFORMATDESCRIPTOR	winPixel; // Describes the pixel format of a drawing surface.
	int						pixelFormat;
};