#ifndef BUFFERS_H
#define BUFFERS_H

#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <GL\glew.h>
#include <tchar.h>

class Buffers
{
public:
	Buffers();
	~Buffers();
	void CreateVertexBuffer(GLuint &vertexBuffer);
	void CreateIndexBuffer(GLuint &indexBuffer);
	void DeleteBuffers();

private:
	
};

#endif BUFFERS_H