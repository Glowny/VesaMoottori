#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL\glew.h>
#include <tchar.h>

class Window
{
public:
	Window() {
		className	= L"Testi";
		windowName	= L"Pekka";
		hWindow		= 0;
		hDC			= 0;
		hGLRC		= 0;
		pixFormat	= NULL;
	};

	// Ei voi tällä hetkellä kustomoida kuin nimen, korjataan myöhemmin.
	//Window(TCHAR cName, TCHAR wName) { 
	//	className	= cName;
	//	windowName	= wName;
	//	hWindow		= 0;
	//	hDC			= 0;
	//	hGLRC		= 0;
	//	pixFormat	= NULL; }

	// Prosessoi viestejä ikkunalle.
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	bool Register();
	bool Glew(); // Voisi muokata testaamaan muita GL-versioita.
	void Show();
	void Update();
	~Window() {};

private:
	wchar_t*				className;
	wchar_t*				windowName;
	MSG						messages;
	HWND					hWindow; // Holds window handle.
	WNDCLASSEX				window;
	HDC						hDC; // Private GDI device context.
	HGLRC					hGLRC; // OpenGL rendering context.
	PIXELFORMATDESCRIPTOR	winPixel; // Describes the pixel format of a drawing surface.
	int						pixFormat; 
};