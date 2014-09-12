#include "Debugger.h"


Debugger::Debugger()
{
	
}


Debugger::~Debugger()
{
}

void Debugger::CheckGlew()
{

	//if(GLEW_OK!=glewInit())
	GLenum error = glewInit();
	if (error == GLEW_OK)
	{
		Type("Glew succeeded!");
	}
	else
		Type("GLEW failed! "); std::cout << glewGetErrorString(error);
	//exit(1); // GLEW failed!

	if (GLEW_VERSION_2_1)
		Type("OpenGL 2.1 supported.");
	else
		Type("OpenGL not 2.1 supported.");
	//MessageBoxA(0, "2.1 SUPPORTED", "OPENGL VERSION", 0);


}

void Debugger::Type(std::string value)  //TYPES VALUES USING STD::COUT
{
	std::cout << value << std::endl;
}

void Debugger::Variable(int vi)
{
	std::cout << vi;
}

void Debugger::Variable(float vf)
{
	std::cout << vf;
}

void Debugger::Variable(double vd)
{
	std::cout << vd;
}

void Debugger::Variable(std::string vs)
{
	std::cout << vs;
}

void Debugger::Variable(char vc)
{
	std::cout << vc;
}