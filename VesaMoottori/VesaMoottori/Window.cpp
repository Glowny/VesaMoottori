#include "Window.h"
#include <iostream>

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
	return true;
}

// Normi ikkunassa ei ole update/draw funktioita vielä.
/* void Window::Show()
{
	ShowWindow(hWindow, SW_SHOWNORMAL);
}

void Window::Update()
{
	UpdateWindow(hWindow);
	SwapBuffers(hDC);
} */

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