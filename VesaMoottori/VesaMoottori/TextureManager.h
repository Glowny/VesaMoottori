#pragma once
#include <vector>
#include "ImageInfo.h"
#include <GL\glew.h>

// juu ei hirveesti manageroi, ku opengl:ss� on indeksill� samat jutut. Vois varmaan laittaa mapilla tai samanlailla indeksill�.

class TextureManager
{
public:
	TextureManager() {};
	~TextureManager() {};

	GLuint CreateTexture(ImageInfo image);
	void DestroyTexture(GLuint index);

private:
	std::vector<GLuint*> textureIndex;
};



