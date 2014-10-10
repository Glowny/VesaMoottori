#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>

class Window
{
public:
	Window() {
		className		= L"Testi";
		windowName		= L"Pekka";
		windowHandle	= 0;
		deviceContext	= 0;
	};

	// Ei voi t�ll� hetkell� kustomoida kuin nimen, korjataan my�hemmin.
	//Window(TCHAR cName, TCHAR wName) { 
	//	className	= cName;
	//	windowName	= wName;
	//	hWindow		= 0;
	//	hDC			= 0;
	//	hGLRC		= 0;
	//	pixFormat	= NULL; }

	// Prosessoi viestej� ikkunalle.
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool Register();
	~Window() {};

	//void Show();
	//void Update();

	HDC GetDevice() { return deviceContext; }
	HWND GetHandle() { return windowHandle; }

private:
	wchar_t*				className;
	wchar_t*				windowName;
	HWND					windowHandle; // Holds window handle.
	HDC						deviceContext; // Private GDI device context.
	WNDCLASSEX				win;
};