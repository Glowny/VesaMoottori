#include <GL\glew.h>

class Buffers
{
public:
	GLuint CreateBuffers(const void *bufferData, GLsizei bufferSize);
	GLuint BindBuffers(GLuint bufferName);
	GLuint UnBindBuffers();
	GLuint GetBuffer(GLuint target);

	//GLuint CreateIndexBuffers(const void *bufferData, GLsizei bufferSize);
	//GLuint CreateBuffers();


private:
	
};

//glDeleteBuffers(1, &vertexBuffer);
//glDeleteBuffers(1, &indexBuffer);