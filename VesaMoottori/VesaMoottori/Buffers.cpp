#include "Buffers.h"

static const GLfloat vertexData[] =
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

void Buffers::CreateVertexBuffer(GLuint &vertexBuffer)
{
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
}

void Buffers::CreateIndexBuffer(GLuint &indexBuffer)
{
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
}

void Buffers::DeleteBuffers()
{

}
