#pragma once
#include "Window.h"

class GraphicsDevice
{
public:
	GraphicsDevice();
	GraphicsDevice(std::string name, int width, int height);
	
	bool Register();
	bool Glew();
	bool Update(MSG &messages);
	void Display();
	void SetWindow(Window &window);
	bool IsOpen();
	
	void Show();
	void Clear();
	
	vector2i GetSize();

	~GraphicsDevice();

private:
	Window*					window;
	HGLRC					renderingContext; // OpenGL rendering context.
	PIXELFORMATDESCRIPTOR	winPixel; // Describes the pixel format of a drawing surface.
	int						pixelFormat;
};