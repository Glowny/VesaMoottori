#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <GL\glew.h>
#include <GL\GLU.h>
#include <GL\GL.h>


class Debugger
{
public:
	Debugger();
	~Debugger();
	void CheckGlew();
	void Type(std::string value);
	void Variable(int vi); void Variable(float vf); void Variable(double vd); void Variable(std::string vs); void Variable(char vc);
	template <typename T>
	void VariableT(T);

private:
};


#endif

