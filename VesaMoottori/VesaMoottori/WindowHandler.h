#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>

class WindowHandler
{
public:
	static bool Initialize();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static HWND *windowHandle;
	WindowHandler() {};
	~WindowHandler() {};
};