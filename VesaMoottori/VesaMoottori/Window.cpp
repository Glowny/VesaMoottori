#include "Window.h"
#include <iostream>

Window::Window()
{
	className			= L"Win";
	windowName			= L"Window";
	windowHandle		= 0;
	deviceContext		= 0;
	style				= 0;
	clientArea.left		= 0;
	clientArea.top		= 0;
	clientArea.right	= 500;
	clientArea.bottom	= 500;
	style				= WS_OVERLAPPEDWINDOW;
	opened				= false;
}

Window::Window(std::string name, int width, int height)
{
	className			= L"Win";
	windowName			= L"Window"; // Custom nimi TO-DO.
	windowHandle		= 0;
	deviceContext		= 0;
	style				= 0;
	clientArea.left		= 0;
	clientArea.top		= 0;
	clientArea.right	= width;
	clientArea.bottom	= height;
	style				= WS_OVERLAPPEDWINDOW;
	opened				= false;
}

// Alustaa ja rekisteröi windows-ikkunan. Ei voi tällä hetkellä kustomoida ollenkaan, korjataan myöhemmin.
bool Window::Register()
{
	AdjustWindowRectEx(&clientArea, style, FALSE, 0);
	win.lpfnWndProc		= WndProc;
	win.cbSize			= sizeof(WNDCLASSEX);
	win.style			= CS_OWNDC;
	win.hInstance		= GetModuleHandle(nullptr); // Jos tulee onglemia HINSTANCE pitää saada mainin kautta.
	win.hbrBackground	= CreateSolidBrush(RGB(0, 0, 0));
	win.lpszClassName	= className;
	win.cbClsExtra		= NULL;
	win.cbWndExtra		= NULL;
	win.hIcon			= NULL;
	win.hCursor			= NULL;
	win.lpszMenuName	= NULL;
	win.hIconSm			= NULL;

	if(!RegisterClassEx(&win)) // Rekisteröidään ikkuna ja tarkistetaan onnistuuko se.
	{
		std::cout << "RegisterClassEx failed!" << std::endl;
		return false;
	}
	else
		std::cout << "RegisterClassEx succeeded!" << std::endl;

	// Luodaan ikkuna ja sille handle jonka kautta sitä voidaan käyttää.
	windowHandle = CreateWindowEx(
		NULL,
		className,
		windowName,
		style,
		0, 0,
		clientArea.right - clientArea.left,
		clientArea.bottom - clientArea.top,
		NULL, NULL,
		win.hInstance,
		NULL);

	if(!windowHandle) // Tarkastetaan handlen luominen.
	{
		std::cout << "WindowHandle failed!" << std::endl;
		return false;
	}
	else
		std::cout << "WindowHandle succeeded!" << std::endl;

	deviceContext = GetDC(windowHandle); // Asetetaan arvo aiemmin alustetulle device contextille.
	opened = true;
	return true;
}

HDC Window::GetDevice()
{
	return deviceContext;
}

HWND Window::GetHandle()
{
	return windowHandle;
}

void Window::CloseWindow()
{
	opened = false;
}

void Window::OpenWindow()
{
	opened = true;
}

bool Window::IsOpen()
{
	return opened;
}

void Window::SetSize(int width, int height)
{
	if(opened)
		DestroyWindow(windowHandle);
	clientArea.right	= width;
	clientArea.bottom	= height;
	Register();
}

void Window::Update(MSG &messages)
{
	while (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE)) // Ikkuna ottaa vastaan viestejä.
	{
		if (messages.message == WM_QUIT)
		{
			// Tuhotaan ikkuna.
			break;
		}
		DispatchMessage(&messages);
	}
}

vector2i Window::GetSize()
{
	return vector2i(clientArea.right, clientArea.bottom);
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
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

Window::~Window()
{
	delete className;
	delete windowName;
}