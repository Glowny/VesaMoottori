#pragma once
#include <GL\glew.h>
struct TextureBuffer
{
	GLuint arrayLocation;
	GLsizei dataSize;
	GLuint elementArrayLocation;
	GLsizei indexSize;
};