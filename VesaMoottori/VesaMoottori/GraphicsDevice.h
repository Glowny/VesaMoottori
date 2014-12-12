#pragma once
#include "Window.h"

class GraphicsDevice
{
public:
	GraphicsDevice();
	GraphicsDevice(std::string name, int width, int height);
	~GraphicsDevice();
	
	bool Register();
	bool Glew();
	bool Update(MSG &messages);
	void Display();
	bool IsOpen();
	void Clear();

	void SetWindow(Window &window);
	void SetClearColor(float red, float green, float blue);
	vector2i GetSize();

private:
	Window*					window;
	HGLRC					renderingContext; // OpenGL rendering context.
	PIXELFORMATDESCRIPTOR	winPixel; // Describes the pixel format of a drawing surface.
	int						pixelFormat;
};