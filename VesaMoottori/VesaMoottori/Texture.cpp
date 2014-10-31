#include "Texture.h"

Texture::Texture(Image *image)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Ei ole hyvin kustomoitu tämä texture.
	// Voi luoda ainoastaan alpha-channel PNG.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		image->width,
		image->height,
		0, GL_RGBA, GL_UNSIGNED_BYTE,
		image->decodedImage.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0u);
}

//void Texture::DestroyTexture(GLuint index)
//{
//	glDeleteTextures(1, &index);
//}