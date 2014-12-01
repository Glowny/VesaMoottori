#include "Texture.h"

Texture::Texture()
{
}

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

vector2i Texture::GetSize()
{
	return vector2i(image->width, image->height);
}

Texture::~Texture()
{
	// Tee myöhemmin.
	//glDeleteTextures(1, &textureIndex);
}

//void Texture::CreateBuffer(const void *data, GLsizei dataSize, const void *index, GLsizei indexSize)
//{
//	// tämä tuottaa ongelmia: jos halutaan piirtää kaksi tekstuuria vaikka eri paikkoihin, buffereita pitää tehdä
//	// myös kaksi, kun ne pitäs laittaa yhteen bufferiin. Siiretään spritebatchiin.
//	GLuint tempIndex;
//	buffer.dataSize = dataSize;
//	buffer.indexSize = indexSize;
//
//	glGenBuffers(1, &tempIndex); // Returns a list of integers that are not currently used as buffer names.
//	glBindBuffer(GL_ARRAY_BUFFER, tempIndex); // Buffer created on bind.
//	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
//	buffer.arrayLocation = tempIndex;
//
//	glGenBuffers(1, &tempIndex);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempIndex);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, index, GL_STATIC_DRAW);
//	buffer.elementArrayLocation = tempIndex;
//}