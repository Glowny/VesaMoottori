#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdarg.h>

class Debugger
{
public:
	void WriteToConsole(const char* message, ...)
	{
		va_list args;
		va_start(args, message);
		vfprintf(stderr, message, args);
		va_end(args);
	}
	

};

#endif