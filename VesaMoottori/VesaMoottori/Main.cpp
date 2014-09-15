#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>

#include <GL\glew.h>
#include <GL\GLU.h>
#include <GL\GL.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int main()
{
	const TCHAR windowName[] = TEXT("Window");
	const TCHAR windowClassName[] = TEXT("Window");
	MSG messages;

	WNDCLASSEX window; // M‰‰ritell‰‰n tulevan ikkunan asetukset.
	window.lpfnWndProc = WndProc;
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

	if (!RegisterClassEx(&window)) // Rekisterˆid‰‰n ikkuna.
	{
		MessageBox(NULL,
			_T("RegisterClassEx failed!"),
			_T("Viesti"),
			NULL);
	}
	else
		std::cout << "RegisterClassEx succeeded!" << std::endl;

	HWND windowHandle = CreateWindowEx( // Luodaan ikkuna ja sille handle jonka kautta sit‰ voidaan k‰ytt‰‰.
		0,
		windowName,
		windowClassName,
		/*WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX |*/ WS_OVERLAPPEDWINDOW,
		200, 200,
		500, 500,
		0, 0,
		window.hInstance,
		0);

	if (!windowHandle)
		std::cout << "WindowHandle failed!" << std::endl;
	else
		std::cout << "WindowHandle succeeded!" << std::endl;

	ShowWindow(windowHandle, SW_SHOWNORMAL); // N‰ytet‰‰n ikkuna.
	UpdateWindow(windowHandle);

	while (GetMessage(&messages, NULL, 0, 0)) // Main loop jossa ikkuna ottaa vastaan viestej‰.
	{
		TranslateMessage(&messages);
		DispatchMessage(&messages);
	}

	return (int) messages.wParam;

	//if(GLEW_OK!=glewInit())
	//GLenum error = glewInit();
	//if (error == GLEW_OK)
	//	std::cout << "GLEW succeeded!" << std::endl;
	//else
	//	std::cout << "GLEW failed! " << glewGetErrorString(error) << std::endl;
	//	//exit(1); // GLEW failed!

	//if(GLEW_VERSION_2_1)
	//	std::cout << "OpenGL 2.1 supported." << std::endl;
	//else
	//	std::cout << "OpenGL not 2.1 supported." << std::endl;
	//	//MessageBoxA(0, "2.1 SUPPORTED", "OPENGL VERSION", 0);
	//
	//system("pause");
	//return 0;
}

// Prosessoi viestej‰ ikkunalle.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT paint; // Can be used to paint the client area of a window owned by that application.
	HDC displayHandle; // Mihin piirret‰‰n.
	TCHAR greeting[] = _T("VesaMoottori");

	switch (message) {
	case WM_PAINT:
		displayHandle = BeginPaint(hWnd, &paint);
		TextOut(displayHandle, 5, 5, greeting, _tcslen(greeting));
		EndPaint(hWnd, &paint);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam); 
		break;
	}

	return 0;
}