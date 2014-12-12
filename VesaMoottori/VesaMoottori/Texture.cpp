#include "Texture.h"

Texture::Texture(Image *image)
{
	this->image = image;

	glGenTextures(1, &textureIndex);
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Ei ole hyvin kustomoitu tämä texture.
	// Voi luoda ainoastaan alpha-channel PNG.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		image->width,
		image->height,
		0, GL_RGBA, GL_UNSIGNED_BYTE,
		image->decodedImage.data());
}

GLuint Texture::GetIndex()
{
	return textureIndex;
}

vector2f Texture::GetSize()
{
	return vector2f((float)image->width, (float)image->height);
}

Texture::~Texture()
{
	// Tee myöhemmin.
	//glDeleteTextures(1, &textureIndex);
}