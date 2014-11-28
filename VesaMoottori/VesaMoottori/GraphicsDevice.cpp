#include "GraphicsDevice.h"
#include <iostream>
#include <GL\glew.h>

GraphicsDevice::GraphicsDevice()
{
	window = new Window();
	renderingContext = 0;
	pixelFormat = 0;	
	if(Register())
		std::cout << "GraphicsDevice created." << std::endl;
	else
		std::cout << "GraphicsDevice failed." << std::endl;
}

GraphicsDevice::GraphicsDevice(std::string name, int width, int height)
{
	window = new Window(name, width, height);
	renderingContext = 0;
	pixelFormat = 0;
	if(Register())
		std::cout << "GraphicsDevice created." << std::endl;
	else
		std::cout << "GraphicsDevice failed." << std::endl;
}

bool GraphicsDevice::Register()
{
	winPixel.nSize			= sizeof(PIXELFORMATDESCRIPTOR);
	winPixel.nVersion		= 1;
	winPixel.dwFlags		= PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | LPD_SUPPORT_OPENGL;
	winPixel.iPixelType		= PFD_TYPE_RGBA;
	winPixel.cColorBits		= 24;
	winPixel.cDepthBits		= 24;

	pixelFormat = ChoosePixelFormat(window->GetDevice(), &winPixel); // Etsitään lähin pixeliformaatti jota voidaan käyttää.
	if(!SetPixelFormat(window->GetDevice(), pixelFormat, &winPixel))
		std::cout << "SetPixelFormat failed!" << std::endl;
	else
		std::cout << "SetPixelFormat succeeded!" << std::endl;

	renderingContext = wglCreateContext(window->GetDevice()); // Luodaan handle OpenGL renderöintiä varten.
	wglMakeCurrent(window->GetDevice(), renderingContext); // Käytetään tätä ikkunaa komentokutsuissa.

	if(Glew())
	{
		ShowWindow(window->GetHandle(), SW_SHOWNORMAL);
		return true;
	}
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

	if(GLEW_VERSION_2_1) // Tarkastetaan onko 2.1 käytössä.
		std::cout << "OpenGL 2.1 supported." << std::endl;
	else
	{
		std::cout << "OpenGL 2.1 not supported." << std::endl;
		return false;
	}

	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void GraphicsDevice::SetWindow(Window &window)
{
	(this->window) = &window;
	if(Register())
		std::cout << "GraphicsDevice (SetWindow) succeed." << std::endl;
	else
		std::cout << "GraphicsDevice (SetWindow) fail." << std::endl;
}

bool GraphicsDevice::Update(MSG &messages)
{
	// Ei vissiin tarvitse mitään OpenGL tarkistuksia.
	if(window->Update(messages))
		return true;
	else
		return false;
}

void GraphicsDevice::Display()
{
	UpdateWindow(window->GetHandle());
	SwapBuffers(window->GetDevice());
}

void GraphicsDevice::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

bool GraphicsDevice::IsOpen()
{
	//return window->IsOpen();
	// Koodataan myöhemmin paremmat ikkuna-komennot jos on tarvetta.
	return true;
}

vector2i GraphicsDevice::GetSize()
{
	return window->GetSize();
}

GraphicsDevice::~GraphicsDevice()
{
	wglDeleteContext(renderingContext); // Tuhotaan renderöinti sisältö - pitää vielä koodata windowiin.
	delete window;
}

//bool GraphicsDevice::Close()
//{
//	return window->Close();
//}

//void GraphicsDevice::Show()
//{
//	ShowWindow(window->GetHandle(), SW_SHOWNORMAL);
//}