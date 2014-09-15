#include "WindowHandler.h"
HWND *WindowHandler::windowHandle;

LRESULT WindowHandler::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		return 0;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

bool WindowHandler::Initialize()
{
	const TCHAR windowName[] = TEXT("Window");
	const TCHAR windowClassName[] = TEXT("Window");

	WNDCLASSEX window;
	window.lpfnWndProc = WindowHandler::WndProc;
	window.cbSize = sizeof(WNDCLASSEX);
	window.style = CS_OWNDC;
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	window.hInstance = GetModuleHandle(nullptr);
	window.hIcon = 0;
	window.hCursor = 0;
	window.hbrBackground = 0;
	window.lpszMenuName = 0;
	window.lpszClassName = windowClassName;
	window.hIconSm = 0;

	if (!RegisterClassEx(&window))
	{
		MessageBox(NULL,
			_T("RegisterClassEx failed!"),
			_T("Viesti"),
			NULL);
		return false;
	}
	else
		std::cout << "RegisterClassEx succeeded!" << std::endl;

	HWND tempHandle = CreateWindowEx(
		0,
		windowName,
		windowClassName,
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		200, 200,
		500, 500,
		0,
		0,
		window.hInstance,
		0);

	if (!windowHandle)
	{
		std::cout << "WindowHandle failed!" << std::endl;
		return false;
	}
	else
	{
		std::cout << "WindowHandle succeeded!" << std::endl;
		//WindowHandler::windowHandle = tempHandle;
		return true;
	}
}