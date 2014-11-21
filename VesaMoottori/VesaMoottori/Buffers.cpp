#include "Buffers.h"
#include <iostream>

TextureBuffer Buffers::CreateTextureBuffer(const void *data, GLsizei dataSize, const void *index, GLsizei indexSize)
{
	GLuint buffer;
	TextureBuffer tempBuffer;
	tempBuffer.dataSize = dataSize;
	tempBuffer.indexSize = indexSize;
	GLuint buffer[2];
	glGenBuffers(2, &buffer[0]); // Returns a list of integers that are not currently used as buffer names.
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]); // Buffer created on bind.
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	tempBuffer.arrayLocation = buffer[0];

	//glGenBuffers(1, &buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, index, GL_STATIC_DRAW);
	tempBuffer.elementArrayLocation = buffer[1];

	return tempBuffer;
}

/*SpriteBuffer Buffers::CreateSpriteBuffer(const void *data, GLsizei dataSize, const void *index, GLsizei indexSize)
{
	GLuint buffer;
	SpriteBuffer tempBuffer;
	tempBuffer.dataSize = dataSize;
	tempBuffer.indexSize = indexSize;

	glGenBuffers(1, &buffer); // Returns a list of integers that are not currently used as buffer names.
	glBindBuffer(GL_ARRAY_BUFFER, buffer); // Buffer created on bind.
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	tempBuffer.arrayLocation = buffer;

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, index, GL_STATIC_DRAW);
	tempBuffer.elementArrayLocation = buffer;

	return tempBuffer;
}

 GLuint Buffers::CreateBuffers(const void *bufferData, GLsizei bufferSize)
{
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, bufferData, GL_STATIC_DRAW);
	return buffer;
}
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
GLuint Buffers::CreateIndexBuffers(const void *bufferData, GLsizei bufferSize)
{
<<<<<<< HEAD
	return target;
}


GLuint Buffers::CreateIndexBuffers(const void *bufferData, GLsizei bufferSize)
{
	GLuint buffer;

		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, bufferData, GL_STATIC_DRAW);
	
	return buffer;
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

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, bufferData, GL_STATIC_DRAW);
	return buffer;
} */