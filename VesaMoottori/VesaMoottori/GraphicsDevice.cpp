#include "GraphicsDevice.h"
#include <iostream>
#include <GL\glew.h>

bool GraphicsDevice::Register()
{
	window.Register(); // Alustetaan normaali windows-ikkuna.

	winPixel.nSize			= sizeof(PIXELFORMATDESCRIPTOR);
	winPixel.nVersion		= 1;
	winPixel.dwFlags		= PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | LPD_SUPPORT_OPENGL;
	winPixel.iPixelType		= PFD_TYPE_RGBA;
	winPixel.cColorBits		= 24;
	winPixel.cDepthBits		= 24;

	pixelFormat = ChoosePixelFormat(window.GetDevice(), &winPixel); // Etsit‰‰n l‰hin pixeliformaatti jota voidaan k‰ytt‰‰.
	if(!SetPixelFormat(window.GetDevice(), pixelFormat, &winPixel))
		std::cout << "SetPixelFormat failed!" << std::endl;
	else
		std::cout << "SetPixelFormat succeeded!" << std::endl;

	renderingContext = wglCreateContext(window.GetDevice()); // Luodaan handle OpenGL renderˆinti‰ varten.
	wglMakeCurrent(window.GetDevice(), renderingContext); // K‰ytet‰‰n t‰t‰ ikkunaa komentokutsuissa.

	if(Glew())
		return true;
	else
		return false;
}   

bool GraphicsDevice::Glew()
{
	GLenum error = glewInit(); // Alustetaan Glew.
	if(error == GLEW_OK)
		std::cout << "GLEW succeeded!" << std::endl;
	else
	{
		std::cout << "GLEW failed, error message: " << glewGetErrorString(error) << std::endl;
		return false;
	}

	if(GLEW_VERSION_2_1) // Tarkastetaan onko 2.1 k‰ytˆss‰.
		std::cout << "OpenGL 2.1 supported." << std::endl;
	else
	{
		std::cout << "OpenGL 2.1 not supported." << std::endl;
		return false;
	}

	glClearColor(0.0f, 0.8f, 0.0f, 0.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void GraphicsDevice::Update()
{
	UpdateWindow(window.GetHandle());
	SwapBuffers(window.GetDevice());
}

void GraphicsDevice::Show()
{
	ShowWindow(window.GetHandle(), SW_SHOWNORMAL);
}

void GraphicsDevice::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
}