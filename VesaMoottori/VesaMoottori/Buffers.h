#ifndef BUFFERS_H
#define BUFFERS_H

#include <vector>
#include <GL\glew.h>

class Buffers
{
public:
	Buffers();
	GLuint CreateVertexBuffers(const void *bufferData, GLsizei bufferSize);
	GLuint CreateIndexBuffers(const void *bufferData, GLsizei bufferSize);
	GLuint BindBuffers(GLuint bufferName);
	GLuint UnBindBuffers();

	GLuint GetBuffer(GLuint target);

	GLuint CreateBuffers();

private:
	
};

#endif BUFFERS_H