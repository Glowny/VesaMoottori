#include "Buffers.h"
//
//static const GLfloat triangleData[] =
//{
//	-0.8f, -0.8f, // Positio.
//	1.0f, 0.0f, 0.0f, // Väri.
//	0.0f, 0.0f, // Tekstuuri.
//
//	-0.8f, 0.8f,
//	0.0f, 1.0f, 0.0f,
//	0.0f, -1.0f,
//
//	0.8f, 0.8f,
//	0.0f, 0.0f, 1.0f,
//	1.0f, -1.0f,
//
//	0.8f, -0.8f,
//	0.0f, 0.0f, 1.0f,
//	1.0f, 0.0f
//};
//
//static const GLuint indexData[] = { 0, 1, 2, 3 };

Buffers::Buffers() {}

//CREATING VERTEX BUFFERS
GLuint Buffers::CreateBuffers(const void *bufferData, GLsizei bufferSize)
{
	GLuint buffer;

		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, bufferSize, bufferData, GL_STATIC_DRAW);
	

	return buffer;
}
//CREATING INDEX BUFFERS
//GLuint Buffers::CreateIndexBuffers(const void *bufferData, GLsizei bufferSize)
//{
//	GLuint buffer;
//
//		glGenBuffers(1, &buffer);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, bufferData, GL_STATIC_DRAW);
//	
//	return buffer;
//}

GLuint Buffers::BindBuffers(GLuint bufferName)
{
		glBindBuffer(GL_ARRAY_BUFFER, bufferName);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferName);

	return true;
}

GLuint Buffers::UnBindBuffers()
{

	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	

	return true;
}


GLuint Buffers::GetBuffer(GLuint target) //RETURN BUFFER
{
	return target;
}

//GLuint Buffers::CreateBuffers() //CREATE BUFFERS HERE
//{
//	GLuint buffers[2];
//
//	buffers[0] = CreateVertexBuffers(triangleData, sizeof(triangleData));
//	buffers[1] = CreateIndexBuffers(indexData, sizeof(indexData));
//
//	return *buffers;
//}
