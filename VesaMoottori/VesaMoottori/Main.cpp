#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>

#include <GL\glew.h>
#include <GL\GLU.h>
#include <GL\GL.h>
#include "Debugger.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int main()
{
<<<<<<< HEAD
	const TCHAR windowName[] = TEXT("Window");
	const TCHAR windowClassName[] = TEXT("Window");
	MSG messages;
	bool isRunning = true;

	WNDCLASSEX window; // Määritellään tulevan ikkunan asetukset.
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

	if (!RegisterClassEx(&window)) // Rekisteröidään ikkuna.
=======
	const TCHAR				winName[] = TEXT("Window");
	const TCHAR				winClassName[] = TEXT("Window");
	MSG						messages;
	HGLRC					hRC = NULL; // Permanent rendering context.
	HDC						hDC = NULL; // Private GDI device context.
	HGLRC					hGLRC = NULL; // OpenGL rendering context.
	HWND					winHandle = NULL; // Holds window handle.
	HINSTANCE				hInstance = GetModuleHandle(nullptr); // Instance of the application
	WNDCLASSEX				winClass; // Sisältää ikkunan asetukset.
	PIXELFORMATDESCRIPTOR	winPixel; // Describes the pixel format of a drawing surface.
	bool					isRunning = true;
	int						pixFormat = NULL;

	// Alustetaan windows-ikkkuna.
	winClass.lpfnWndProc	= WndProc;
	winClass.cbSize			= sizeof(WNDCLASSEX);
	winClass.style			= CS_OWNDC;
	winClass.hInstance		= hInstance;
	winClass.hbrBackground	= CreateSolidBrush(RGB(255, 102, 255));
	winClass.lpszClassName	= winClassName;
	winClass.cbClsExtra		= NULL;
	winClass.cbWndExtra		= NULL;
	winClass.hIcon			= NULL;
	winClass.hCursor		= NULL;
	winClass.lpszMenuName	= NULL;
	winClass.hIconSm		= NULL;

	if (!RegisterClassEx(&winClass)) // Rekisteröidään ikkuna ja tarkistetaan onnistuuko se.
>>>>>>> parent of f317c5f... Epilepsia on Parasta
		std::cout << "RegisterClassEx failed!" << std::endl;
	else
		std::cout << "RegisterClassEx succeeded!" << std::endl;

<<<<<<< HEAD
<<<<<<< HEAD
	HWND windowHandle = CreateWindowEx( // Luodaan ikkuna ja sille handle jonka kautta sitä voidaan käyttää.
=======
	winHandle = CreateWindowEx( // Luodaan ikkuna ja sille handle jonka kautta sitä voidaan käyttää.
>>>>>>> parent of f317c5f... Epilepsia on Parasta
=======
	winHandle = CreateWindowEx( // Luodaan ikkuna ja sille handle jonka kautta sitä voidaan käyttää.
>>>>>>> parent of f317c5f... Epilepsia on Parasta
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

	ShowWindow(windowHandle, SW_SHOWNORMAL); // Näytetään ikkuna.
	UpdateWindow(windowHandle);
	
	GLenum error = glewInit(); // Alustetaan Glew.
	if (error == GLEW_OK)
		std::cout << "GLEW succeeded!" << std::endl;
	else
<<<<<<< HEAD
		std::cout << "GLEW failed, error message: " << glewGetErrorString(error) << std::endl;
=======
		std::cout << "SetPixelFormat succeeded!" << std::endl;

	hGLRC = wglCreateContext(hDC); // Luodaan handle OpenGL renderöintiä varten.
	wglMakeCurrent(hDC, hGLRC); // Käytetään tätä ikkunaa komentokutsuissa.

	ShowWindow(winHandle, SW_SHOWNORMAL); // Näytetään rekisteröity ikkuna.
	UpdateWindow(winHandle);
	//GlewTests(); // Testaa OpenGL 2.1 toimivuutta.


	// Jotain testausta.
	glClearColor(1.0f, 0.2f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	

>>>>>>> parent of f317c5f... Epilepsia on Parasta

	if(GLEW_VERSION_2_1) // Tarkastetaan onko 2.1 käytössä.
		std::cout << "OpenGL 2.1 supported." << std::endl;
	else
		std::cout << "OpenGL 2.1 not supported." << std::endl;
	
	while (isRunning) // Ohjelman main-looppi.
	{
		while (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE)) // Main loop jossa ikkuna ottaa vastaan viestejä.
		{
			//TranslateMessage(&messages); // Kääntää näppäin painalluksia tunnetuksi koodiksi.
			if (messages.message == WM_QUIT)
			{
				isRunning = false;
				break;
			}
			/*glClearColor(0.0, 0.0, 0.0, 0.0);*/
			DispatchMessage(&messages);
		}
	}

	//system("pause");
	//return (int) messages.wParam;
	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
// Prosessoi viestejä ikkunalle.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
=======
=======
>>>>>>> parent of f317c5f... Epilepsia on Parasta

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // Prosessoi viestejä ikkunalle.
{ 
>>>>>>> parent of f317c5f... Epilepsia on Parasta
	//PAINTSTRUCT paint; // Can be used to paint the client area of a window owned by that application.
	//HDC displayHandle; // Mihin piirretään.
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
