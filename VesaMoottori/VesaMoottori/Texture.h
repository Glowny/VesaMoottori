#pragma once
#include <GL\glew.h>
#include "lodepng.h"
#include "Image.h"
#include "TextureBuffer.h"

class Texture
{
public:
	Texture() {}; // Default konstruktoria ei tueta atm.
	Texture(Image *image, float position, float size);
	void Draw();
	void CreateBuffer(const void *data, GLsizei dataSize, const void *index, GLsizei indexSize);
	GLuint GetTexture() { return textureIndex; } // Palauttaa bindatun indeksin textureen.
	//void DestroyTexture(GLuint index);
	~Texture() {};

private:
	TextureBuffer buffer;
	GLuint textureIndex; // Texturen bindattu indeksi.
	static GLfloat vertexData[16];
	static const GLuint indexData[6];
};