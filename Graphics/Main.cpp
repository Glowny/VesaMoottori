#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#include <GL\glew.h>
#include <GL\GLU.h>
#include <GL\GL.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int main()
{
	WNDCLASSEX window;
	window.cbSize = sizeof(WNDCLASSEX);
	window.style = CS_OWNDC;
	window.lpfnWndProc = WndProc;
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	window.hInstance = GetModuleHandle(nullptr);
	window.hIcon = NULL;
	window.hCursor = NULL;
	window.hbrBackground = NULL;
	window.lpszMenuName = NULL;
	window.lpszClassName = (LPCTSTR)"Ikkuna";
	window.hIconSm = NULL;

	if (!RegisterClassEx(&window))
	{
		MessageBox(NULL,
			_T("RegisterClassEx failed!"),
			_T("asdasd"),
			NULL);
	}

	HWND windowHandle = CreateWindow(
		_T("IkkunaApp"),
		_T("Titteli"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 100,
		NULL,
		NULL,
		window.hInstance,
		NULL);

	if (!windowHandle)
		std::cout << "WindowHandle failed!" << std::endl;

	ShowWindow(windowHandle, SW_SHOWNORMAL);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//return (int)msg.wParam;

	//if(GLEW_OK!=glewInit())
	GLenum error = glewInit();
	if (error == GLEW_OK)
		std::cout << "GLEW succeeded!" << std::endl;
	else
		std::cout << "GLEW failed! " << glewGetErrorString(error) << std::endl;
		//exit(1); // GLEW failed!

	if(GLEW_VERSION_2_1)
		std::cout << "OpenGL 2.1 supported." << std::endl;
	else
		std::cout << "OpenGL not 2.1 supported." << std::endl;
		//MessageBoxA(0, "2.1 SUPPORTED", "OPENGL VERSION", 0);
	
	system("pause");
	return 0;
}