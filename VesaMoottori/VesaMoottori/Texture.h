#pragma once
#include <GL\glew.h>
#include "lodepng.h"
#include "Image.h"
#include "TextureBuffer.h"
#include "vector2.h"

class Texture
{
public:
<<<<<<< HEAD
	Texture(); // Ei tueta.
	Texture(Image *image);
	GLuint GetIndex();
	vector2i GetSize();
	~Texture();
=======
	Texture() {}; // Default konstruktoria ei tueta atm.
>>>>>>> parent of 6d13cfe... Backup I

	Texture(Image *image, vector2f position, float scale);
	void Draw();

	void SetPosition(vector2f position);
	vector2f GetSize()
	{
		return vector2f((float)(image->width), (float)(image->height));
	}
	void SetScale(float scale) {
		(this->scale) = scale;
	}

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
	GLfloat scale;
	vector2f position;
	Image *image;
	GLfloat vertexData[28];
	GLuint indexData[6];
	//const GLuint indexData[6];
};