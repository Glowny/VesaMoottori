#include <GL\glew.h>
#include "SpriteBuffer.h"

class Buffers
{
public:
	//GLuint CreateBuffers(const void *bufferData, GLsizei bufferSize);
	//GLuint BindBuffers(GLuint bufferName);
	//GLuint UnBindBuffers();
	//GLuint GetBuffer(GLuint target);
	//GLuint CreateIndexBuffers(const void *bufferData, GLsizei bufferSize);
	//GLuint CreateBuffers();

	// Tuukan Bufferit
	SpriteBuffer CreateSpriteBuffer(const void *data, GLsizei dataSize, const void *index, GLsizei indexSize);
};

//glDeleteBuffers(1, &vertexBuffer);
//glDeleteBuffers(1, &indexBuffer);