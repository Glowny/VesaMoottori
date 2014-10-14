#include "TextureManager.h"

GLuint TextureManager::CreateTexture(ImageInfo image)
{
	glEnable(GL_TEXTURE_2D);
	GLuint texture;
	textureIndex.push_back(&texture);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image.decodedImage[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0u);
	return texture;
}

void TextureManager::DestroyTexture(GLuint index)
{
	glDeleteTextures(1, &index);
	// vektoristakin pois.
}