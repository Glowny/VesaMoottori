#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>

class Window
{
public:
	Window() {
		className			= L"Win";
		windowName			= L"Window";
		windowHandle		= 0;
		deviceContext		= 0;
		style				= 0;
		clientArea.left		= 0;
		clientArea.top		= 0;
		clientArea.right	= 500;
		clientArea.bottom	= 500;
		style				= WS_OVERLAPPEDWINDOW;
	};

	Window(std::string name, int width, int height) {
		className			= L"Win";
		/* Ikkunalle custom-nimen luonti:
		wchar_t* widestr = new wchar_t[name.length() + 1];
		std::copy(name.begin(), name.end(), widestr);
		widestr[name.length] = 0; */
		windowName			= L"TO-DO";
		windowHandle		= 0;
		deviceContext		= 0;
		style				= 0;
		clientArea.left		= 0;
		clientArea.top		= 0;
		clientArea.right	= width;
		clientArea.bottom	= height;
		style				= WS_OVERLAPPEDWINDOW;
	}

	// Prosessoi viestejä ikkunalle.
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool Register();
	HDC GetDevice() { return deviceContext; }
	HWND GetHandle() { return windowHandle; }
	~Window() {};

private:
	wchar_t*				className;
	wchar_t*				windowName;
	HWND					windowHandle; // Holds window handle.
	HDC						deviceContext; // Private GDI device context.
	WNDCLASSEX				win;
	DWORD					style;
	RECT					clientArea;
};