#include <GL\glew.h>
#include "SpriteBuffer.h"

class Buffers
{
public:
<<<<<<< HEAD
	GLuint CreateBuffers(const void *bufferData, GLsizei bufferSize);
	GLuint CreateIndexBuffers(const void *bufferData, GLsizei bufferSize); // !!!
	GLuint BindBuffers(GLuint bufferName);
	GLuint UnBindBuffers();
	GLuint GetBuffer(GLuint target);
=======
	SpriteBuffer CreateSpriteBuffer(const void *data, GLsizei dataSize, const void *index, GLsizei indexSize);
>>>>>>> origin/master

};

//GLuint CreateBuffers(const void *bufferData, GLsizei bufferSize);
//GLuint BindBuffers(GLuint bufferName);
//GLuint UnBindBuffers();
//GLuint GetBuffer(GLuint target);
//GLuint CreateIndexBuffers(const void *bufferData, GLsizei bufferSize);
//GLuint CreateBuffers();
//glDeleteBuffers(1, &vertexBuffer);
//glDeleteBuffers(1, &indexBuffer);