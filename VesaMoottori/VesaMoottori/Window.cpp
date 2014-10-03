#include "Window.h"
#include <iostream>

// Alustaa ja rekister�i ikkunan. Ei voi t�ll� hetkell� kustomoida ollenkaan, korjataan my�hemmin.
bool Window::Register()
{
	window.lpfnWndProc		= WndProc;
	window.cbSize			= sizeof(WNDCLASSEX);
	window.style			= CS_OWNDC;
	window.hInstance		= GetModuleHandle(nullptr); // Jos tulee onglemia HINSTANCE pit�� saada mainin kautta.
	window.hbrBackground	= CreateSolidBrush(RGB(0, 0, 0));
	window.lpszClassName	= className;
	window.cbClsExtra		= NULL;
	window.cbWndExtra		= NULL;
	window.hIcon			= NULL;
	window.hCursor			= NULL;
	window.lpszMenuName		= NULL;
	window.hIconSm			= NULL;

	if(!RegisterClassEx(&window)) // Rekister�id��n ikkuna ja tarkistetaan onnistuuko se.
	{
		std::cout << "RegisterClassEx failed!" << std::endl;
		return false;
	}
	else
		std::cout << "RegisterClassEx succeeded!" << std::endl;

	// Luodaan ikkuna ja sille handle jonka kautta sit� voidaan k�ytt��.
	hWindow = CreateWindowEx(
		NULL,
		className,
		windowName,
		WS_OVERLAPPEDWINDOW,
		200, 200, 500, 500,
		NULL, NULL,
		window.hInstance,
		NULL);

	if(!hWindow) // Tarkastetaan handlen luominen.
	{ 
		std::cout << "WindowHandle failed!" << std::endl;
		return false;
	}
	else
		std::cout << "WindowHandle succeeded!" << std::endl;

	hDC = GetDC(hWindow); // Asetetaan arvo aiemmin alustetulle device contextille.

	// Perus-ikkunan alustus tehty, sitten alustetaan OpenGL varten.
	winPixel.nSize			= sizeof(PIXELFORMATDESCRIPTOR);
	winPixel.nVersion		= 1;
	winPixel.dwFlags		= PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | LPD_SUPPORT_OPENGL;
	winPixel.iPixelType		= PFD_TYPE_RGBA;
	winPixel.cColorBits		= 24;
	winPixel.cDepthBits		= 24;

	pixFormat = ChoosePixelFormat(hDC, &winPixel); // Etsit��n l�hin pixeliformaatti jota voidaan k�ytt��.
	if(!SetPixelFormat(hDC, pixFormat, &winPixel))
		std::cout << "SetPixelFormat failed!" << std::endl;
	else
		std::cout << "SetPixelFormat succeeded!" << std::endl;

	hGLRC = wglCreateContext(hDC); // Luodaan handle OpenGL render�inti� varten.
	wglMakeCurrent(hDC, hGLRC); // K�ytet��n t�t� ikkunaa komentokutsuissa.

	if(Glew())
		return true;
	else
		return false;
}

bool Window::Glew()
{
	GLenum error = glewInit(); // Alustetaan Glew.
	if(error == GLEW_OK)
		std::cout << "GLEW succeeded!" << std::endl;
	else
	{
		std::cout << "GLEW failed, error message: " << glewGetErrorString(error) << std::endl;
		return false;
	}

	if(GLEW_VERSION_2_1) // Tarkastetaan onko 2.1 k�yt�ss�.
		std::cout << "OpenGL 2.1 supported." << std::endl;
	else
	{
		std::cout << "OpenGL 2.1 not supported." << std::endl;
		return false;
	}
	return true;
}

void Window::Show()
{
	ShowWindow(hWindow, SW_SHOWNORMAL);
}

void Window::Update()
{
	UpdateWindow(hWindow);
	SwapBuffers(hDC);
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_CLOSE: // Sent as a signal that a window or an application should terminate.
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY: // Sent when a window is being destroyed.
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}