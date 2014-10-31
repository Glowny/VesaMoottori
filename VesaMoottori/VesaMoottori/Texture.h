#pragma once
#include <GL\glew.h>
#include "lodepng.h"
#include "Image.h"

class Texture
{
public:
	Texture() {}; // Default konstruktoria ei tueta atm.
	Texture(Image *image);
	~Texture() {};

	GLuint GetTexture() { return texture; } // Palauttaa bindatun indeksin textureen.
	//void DestroyTexture(GLuint index);

private:
	GLuint texture; // Bindattu indeksi.
};