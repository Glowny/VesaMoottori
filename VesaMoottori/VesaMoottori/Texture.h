#pragma once
#include <GL\glew.h>
#include "lodepng.h"
#include "Image.h"
#include "TextureBuffer.h"
#include "vector2.h"

class Texture
{
public:
	Texture(); // Ei tueta.
	Texture(Image *image);
	GLuint GetIndex();
	vector2i GetSize();
	~Texture();

private:
	GLuint textureIndex;
	Image *image;
};