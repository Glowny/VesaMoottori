#pragma once
#include <GL\glew.h>
#include "lodepng.h"
#include "Image.h"
//typedef std::vector<unsigned char> DecodedImage;

class Texture
{
public:
	Texture() {}; // Default konstruktoria ei tueta atm.
	Texture(Image *image);
	~Texture() {};

	GLuint GetTexture() { return texture; } // Palauttaa bindatun indeksin textureen.
	//Texture(std::string picName) // Ladata kuva nimen perusteella suoraan?
	//GLuint CreateTexture(ImageInfo image);
	//void DestroyTexture(GLuint index);

private:
	GLuint texture; // Bindattu indeksi.
	//int width, height; // S�ilytt�� kuvan mittasuhteet.
	//DecodedImage* image; // Texture muista lokaation omaan imageensa.
};