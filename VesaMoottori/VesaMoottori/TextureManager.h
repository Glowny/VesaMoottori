#pragma once
#include <vector>
#include "ImageInfo.h"
#include <GL\glew.h>

// juu ei hirveesti manageroi, ku opengl:ssä on indeksillä samat jutut. Vois varmaan laittaa mapilla tai samanlailla indeksillä.

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



