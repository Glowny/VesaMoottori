#include "Buffers.h"


GLuint Buffers::CreateVertexBuffers(const int amount, const void *bufferData, GLsizei bufferSize)
{
	GLuint *buffer = new GLuint[amount];

	for (int i = 0; i < amount; i++)
	{
		glGenBuffers(1, &buffer[i]);
		glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
		glBufferData(GL_ARRAY_BUFFER, bufferSize, bufferData, GL_STATIC_DRAW);
	}

	return *buffer;
}

GLuint Buffers::CreateIndexBuffers(int amount, const void *bufferData, GLsizei bufferSize)
{
	GLuint *buffer = new GLuint[amount];

	for (int i = 0; i < amount; i++)
	{
		glGenBuffers(1, &buffer[i]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, bufferData, GL_STATIC_DRAW);
	}
	return *buffer;
}