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
	bool isRunning = true;

	WNDCLASSEX window; // M‰‰ritell‰‰n tulevan ikkunan asetukset.
	window.lpfnWndProc = WndProc;
	window.cbSize = sizeof(WNDCLASSEX);
	window.style = CS_OWNDC;
	window.hInstance = GetModuleHandle(nullptr);
	window.hbrBackground = CreateSolidBrush(RGB(255, 102, 255));
	window.lpszClassName = windowClassName;
	window.cbClsExtra = NULL;
	window.cbWndExtra = NULL;
	window.hIcon = NULL;
	window.hCursor = NULL;
	window.lpszMenuName = NULL;
	window.hIconSm = NULL;

	if (!RegisterClassEx(&window)) // Rekisterˆid‰‰n ikkuna.
		std::cout << "RegisterClassEx failed!" << std::endl;
	else
		std::cout << "RegisterClassEx succeeded!" << std::endl;

	HWND windowHandle = CreateWindowEx( // Luodaan ikkuna ja sille handle jonka kautta sit‰ voidaan k‰ytt‰‰.
		NULL,
		windowName,
		windowClassName,
		WS_OVERLAPPEDWINDOW,
		200, 200,
		500, 500,
		NULL, NULL,
		window.hInstance,
		NULL);

	if (!windowHandle)
		std::cout << "WindowHandle failed!" << std::endl;
	else
		std::cout << "WindowHandle succeeded!" << std::endl;

	ShowWindow(windowHandle, SW_SHOWNORMAL); // N‰ytet‰‰n ikkuna.
	UpdateWindow(windowHandle);
	
	GLenum error = glewInit(); // Alustetaan Glew.
	if (error == GLEW_OK)
		std::cout << "GLEW succeeded!" << std::endl;
	else
		std::cout << "GLEW failed, error message: " << glewGetErrorString(error) << std::endl;

	if(GLEW_VERSION_2_1) // Tarkastetaan onko 2.1 k‰ytˆss‰.
		std::cout << "OpenGL 2.1 supported." << std::endl;
	else
		std::cout << "OpenGL 2.1 not supported." << std::endl;
	
	while (isRunning) // Ohjelman main-looppi.
	{
		while (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE)) // Main loop jossa ikkuna ottaa vastaan viestej‰.
		{
			//TranslateMessage(&messages); // K‰‰nt‰‰ n‰pp‰in painalluksia tunnetuksi koodiksi.
			if (messages.message == WM_QUIT)
			{
				isRunning = false;
				break;
			}
			glClearColor(0.0, 0.0, 0.0, 0.0);
			DispatchMessage(&messages);
		}
	}

	//system("pause");
	//return (int) messages.wParam;
	return 0;
}

// Prosessoi viestej‰ ikkunalle.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	//PAINTSTRUCT paint; // Can be used to paint the client area of a window owned by that application.
	//HDC displayHandle; // Mihin piirret‰‰n.
	//TCHAR greeting[] = _T("Terve");

	switch (message) {
	//case WM_PAINT:
	//	displayHandle = BeginPaint(hWnd, &paint);
	//	TextOut(displayHandle, 5, 5, greeting, _tcslen(greeting));
	//	EndPaint(hWnd, &paint);
	//	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam); 
		break;
	}

	return 0;
}