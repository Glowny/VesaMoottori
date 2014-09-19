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
bool GlewTests(); // Palauttaa true jos glew testit onnistuu.
bool InitGL(GLvoid); // Alustetaan OpenGL.
bool DrawGLScene(GLvoid); // Alustetaan ikkuna piirtämistä varten.
//bool CreateGLWindow();
//GLvoid CloseGLWindow(GLvoid); // Vapauttaa asioita kun ohjelma suljetaan.

int main()
{
	const TCHAR		winName[] = TEXT("Window");
	const TCHAR		winClassName[] = TEXT("Window");
	MSG				messages;
	bool			isRunning = true;
	HGLRC			hRC = NULL; // Permanent rendering context.
	HDC				hDC = NULL; // Private GDI device context.
	HWND			winHandle = NULL; // Holds window handle.
	HINSTANCE		hInstance = GetModuleHandle(nullptr); // Instance of the application
	WNDCLASSEX		winClass; // Sisältää ikkunan asetukset.

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

	if (!RegisterClassEx(&winClass)) // Rekisteröidään ikkuna.
		std::cout << "RegisterClassEx failed!" << std::endl;
	else
		std::cout << "RegisterClassEx succeeded!" << std::endl;

	winHandle = CreateWindowEx( // Luodaan ikkuna ja sille handle jonka kautta sitä voidaan käyttää.
		NULL,
		winName,
		winClassName,
		WS_OVERLAPPEDWINDOW,
		200, 200,
		500, 500,
		NULL, NULL,
		hInstance,
		NULL);

	if (!winHandle)
		std::cout << "WindowHandle failed!" << std::endl;
	else
		std::cout << "WindowHandle succeeded!" << std::endl;

	ShowWindow(winHandle, SW_SHOWNORMAL); // Näytetään rekisteröity ikkuna.
	UpdateWindow(winHandle);
	
	GlewTests(); // Testaa OpenGL 2.1 toimivuutta.
	
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
			DispatchMessage(&messages);
		}
	}

	return (int) messages.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // Prosessoi viestejä ikkunalle.
{ 
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

bool GlewTests()
{
	GLenum error = glewInit(); // Alustetaan Glew.
	if (error == GLEW_OK)
		std::cout << "GLEW succeeded!" << std::endl;
	else
	{
		std::cout << "GLEW failed, error message: " << glewGetErrorString(error) << std::endl;
		return false;
	}

	if (GLEW_VERSION_2_1) // Tarkastetaan onko 2.1 käytössä.
		std::cout << "OpenGL 2.1 supported." << std::endl;
	else
	{
		std::cout << "OpenGL 2.1 not supported." << std::endl;
		return false;
	}
	return true;
}

bool InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH); // Enables smooth shading.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Musta tausta.
	glClearDepth(1.0f); // Syvyys bufferin setup.
	//glEnable(GL_DEPTH_TEST); // Syvyys testejä.
	//glDepthFunc(GL_LEQUAL);
	return true;
}

bool DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clearaa ruudun ja syvyys bufferin.
	glLoadIdentity(); // Resettaa modelview matrixin.
	return true;
}

//bool CreateGLWindow()
//{
//	GLuint		PixelFormat;
//}