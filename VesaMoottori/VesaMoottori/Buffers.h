#ifndef BUFFERS_H
#define BUFFERS_H

#include <GL\glew.h>

class Buffers
{
public:
    GLuint CreateBuffers(GLenum target, const void *buffer_data, GLsizei buffer_size);
};

#endif BUFFERS_H