#pragma once
#include <vector>
#include "ImageInfo.h"
#include <GL\glew.h>
class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	GLuint CreateTexture(ImageInfo image);
private:
	std::vector<GLuint*> textureIndex;
};



