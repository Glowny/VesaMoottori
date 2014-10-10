#include "Buffers.h"

static const GLfloat triangleData[] =
{
	//positions
	-0.7f, -0.7f,
	//colors
	1.0f, 0.0f, 0.0f,
	//texture positions
	0.0f, 0.0f,

	0.0f, 0.7f,
	0.0f, 1.0f, 0.0f,
	0.5f, 1.0f,

	0.7f, -0.7f,
	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f
};

static const GLuint indexData[] = { 0, 1, 2 };


Buffers::Buffers()
{

}


Buffers::~Buffers()
{
}

void Buffers::CreateVertexBuffer()
{
	GLuint vBuffer;

	glGenBuffers(1, &vBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
}

void Buffers::CreateIndexBuffer()
{
	GLuint iBuffer;

	glGenBuffers(1, &iBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
}

void Buffers::DeleteBuffers()
{

}
