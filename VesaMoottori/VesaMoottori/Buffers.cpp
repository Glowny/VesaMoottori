#include "Buffers.h"


GLuint Buffers::CreateBuffers(GLenum target, const void *buffer_data, GLsizei buffer_size)
{
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(target, buffer);
	glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
	return buffer;
}
