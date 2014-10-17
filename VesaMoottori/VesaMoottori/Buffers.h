#ifndef BUFFERS_H
#define BUFFERS_H

#include <GL\glew.h>

class Buffers
{
public:
	GLuint CreateVertexBuffers(const int amount, const void *bufferData, GLsizei bufferSize);
	GLuint CreateIndexBuffers(int amount, const void *bufferData, GLsizei bufferSize);
};

#endif BUFFERS_H