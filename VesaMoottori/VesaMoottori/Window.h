#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include "vector2.h"

class Window
{
public:
	// Prosessois viestejä ikkunalle.
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	Window();
	Window(std::string name, int width, int height);
	~Window();

	bool Register();
	HDC GetDevice();
	HWND GetHandle();
	void CloseWindow();
	void OpenWindow();
	bool IsOpen();
	void SetSize(int width, int height);
	void Update(MSG &messages);
	vector2i GetSize();

private:
	wchar_t*		className;
	wchar_t*		windowName;
	HWND			windowHandle; // Holds window handle.
	HDC				deviceContext; // Private GDI device context.
	WNDCLASSEX		win;
	DWORD			style;
	RECT			clientArea;
	bool			opened;
};