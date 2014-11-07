#pragma once
#include <GL\glew.h>
#include "lodepng.h"
#include "Image.h"
#include "TextureBuffer.h"
#include "vector2.h"

class Texture
{
public:
	Texture() {}; // Default konstruktoria ei tueta atm.

	Texture(Image *image, vector2f position, float scale);
	void Draw();

	void SetPosition(vector2f position);
	vector2f GetSize()
	{
		return vector2f(image->width, image->height);
	}
	void SetScale(float scale) {
		(this->scale) = scale;
	}

	void CreateBuffer(const void *data, GLsizei dataSize, const void *index, GLsizei indexSize);
	GLuint GetTexture() { return textureIndex; } // Palauttaa bindatun indeksin textureen.
	//void DestroyTexture(GLuint index);
	~Texture() {};

private:
	TextureBuffer buffer;
	GLuint textureIndex; // Texturen bindattu indeksi.
	GLfloat scale;
	vector2f position;
	Image *image;
	GLfloat vertexData[28];
	GLuint indexData[6];
	//const GLuint indexData[6];
};