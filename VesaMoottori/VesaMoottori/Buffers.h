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
	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void DeleteBuffers();

private:

};

#endif BUFFERS_H