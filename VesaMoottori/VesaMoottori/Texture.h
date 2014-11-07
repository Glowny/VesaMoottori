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
	void SetScale(float scale) {
		(this->scale) = scale;
	}

	void CreateBuffer(const void *data, GLsizei dataSize, const void *index, GLsizei indexSize);
	GLuint GetTexture() { return textureIndex; } // Palauttaa bindatun indeksin textureen.
	//void DestroyTexture(GLuint index);
	~Texture() { delete vertexData; };

private:
	TextureBuffer buffer;
	GLuint textureIndex; // Texturen bindattu indeksi.
	GLfloat scale;
	vector2f position;

	GLfloat *vertexData;
	/*const GLuint indexData[6];*/
	GLuint indexData[6];
};