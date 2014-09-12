#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#include <GL\glew.h>
#include <GL\GLU.h>
#include <GL\GL.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch (uMsg) {
	case WM_CREATE:
		return 0;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

int main()
{
	static const TCHAR title[] = TEXT("sads"), classi[] = TEXT("sadsa");

	WNDCLASSEX window;
	window.cbSize = sizeof(WNDCLASSEX);
	window.style = CS_OWNDC;
	window.lpfnWndProc = WndProc;
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	window.hInstance = GetModuleHandle(nullptr);
	window.hIcon = 0;
	window.hCursor = 0;
	window.hbrBackground = 0;
	window.lpszMenuName = 0;
	window.lpszClassName = title;
	window.hIconSm = 0;

	if (!RegisterClassEx(&window))
	{
		MessageBox(NULL,
			_T("RegisterClassEx failed!"),
			_T("asdasd"),
			NULL);
	}

	//AdjustWindowRectEx(RECT(, WS_OVERLAPPED, false, WS_EX_LAYERED);

	HWND windowHandle = CreateWindowEx(
		0,
		title,
		classi,
		WS_CAPTION | WS_SYSMENU,
		200, 200,
		500, 500,
		0,
		0,
		window.hInstance,
		0);

	if (!windowHandle)
		std::cout << "WindowHandle failed!" << std::endl;

	ShowWindow(windowHandle, SW_SHOWNORMAL);

	//return (int)msg.wParam;

	if(GLEW_OK!=glewInit())
	GLenum error2 = glewInit();
	if (error2 == GLEW_OK)
		std::cout << "GLEW succeeded!" << std::endl;
	else
		std::cout << "GLEW failed! " << glewGetErrorString(error2) << std::endl;
		//exit(1); // GLEW failed!

	if(GLEW_VERSION_2_1)
		std::cout << "OpenGL 2.1 supported." << std::endl;
	else
		std::cout << "OpenGL not 2.1 supported." << std::endl;
		//MessageBoxA(0, "2.1 SUPPORTED", "OPENGL VERSION", 0);
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	system("pause");
	return 0;
}