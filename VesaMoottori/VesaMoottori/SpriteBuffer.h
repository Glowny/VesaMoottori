#pragma once
#include <GL\glew.h>
struct SpriteBuffer
{
	GLuint arrayLocation;
	GLsizei dataSize;
	GLuint elementArrayLocation;
	GLsizei indexSize;
};