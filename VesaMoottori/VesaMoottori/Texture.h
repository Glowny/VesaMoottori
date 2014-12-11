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

	Texture(Image *image);
//	Texture(Image *image, vector2f position, float scale);
	//void Draw(); Ei piirretä itekseen ei tarvita

	//void SetPosition(vector2f position); Spriten kautta sijainti ei tarvita
	vector2f GetSize()		// ehkä tarvitaa
	{
		return vector2f((float)(image->width), (float)(image->height));
	}
	//void SetScale(float scale) {		// spriten kautta koon muutos, ei tarvita.
	//	(this->scale) = scale;
	//}

	void CreateBuffer(const void *data, GLsizei dataSize, const void *index, GLsizei indexSize);
	GLuint GetTexture() { return textureIndex; } // Palauttaa bindatun indeksin textureen.
	//void DestroyTexture(GLuint index);
	~Texture() {};
	GLuint getTextureIndex()
	{
		return textureIndex;
	}
private:
	TextureBuffer buffer;
	GLuint textureIndex;
	//GLfloat scale;
	//vector2f position;
	Image *image;
	GLfloat vertexData[28];
	GLuint indexData[6];
	//const GLuint indexData[6];
};