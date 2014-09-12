#pragma once
#include <windows.h>
#define WIN32_LEAN_AND_MEAN
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

class WindowHandler
{
public:
	//static WindowHandler* getInstance();
	static bool Initialize();

private:
	WindowHandler() {};
	~WindowHandler() {};
	//LRESULT *procPointer;
	//WNDCLASSEX *winPoint; // Pointer to the window.
};