#include "Texture.h"

Texture::Texture(DecodedImage *image, int width, int height)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Texture class sisältää kuvan tiedot.
	this->width = width;
	this->height = height;
	this->image = image;

	// Ei ole hyvin kustomoitu tämä texture.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		width,
		height,
		0, GL_RGBA, GL_UNSIGNED_BYTE,
		image->data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0u);
}

/* GLuint Texture::CreateTexture(DecodedImage image)
{
	//glEnable(GL_TEXTURE_2D);
	//GLuint texture;
	//textureIndex.push_back(&texture);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image.decodedImage[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0u);
	return texture;
}

void Texture::DestroyTexture(GLuint index)
{
	glDeleteTextures(1, &index);
} */