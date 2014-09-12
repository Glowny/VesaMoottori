#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#include <GL\glew.h>
#include <GL\GLU.h>
#include <GL\GL.h>

int main()
{
	//if(GLEW_OK!=glewInit())
	GLenum error = glewInit();
	if (error == GLEW_OK)
		std::cout << "GLEW succeeded!" << std::endl;
	else
		std::cout << "GLEW failed! " << glewGetErrorString(error) << std::endl;
		//exit(1); // GLEW failed!

	if(GLEW_VERSION_2_1)
		std::cout << "OpenGL 2.1 supported." << std::endl;
	else
		std::cout << "OpenGL not 2.1 supported." << std::endl;
		//MessageBoxA(0, "2.1 SUPPORTED", "OPENGL VERSION", 0);
	
	system("pause");
	return 0;
}