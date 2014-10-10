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
    GLuint CreateBuffers(GLenum target, const void *buffer_data, GLsizei buffer_size);

private:

};

#endif BUFFERS_H