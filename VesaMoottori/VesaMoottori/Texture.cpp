#include "Texture.h"

GLfloat Texture::vertexData[16] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

const GLuint Texture::indexData[6] = { 0, 1, 2, 0, 2, 3 };

Texture::Texture(Image *image, float position, float size)
{
	glGenTextures(1, &textureIndex);
	glBindTexture(GL_TEXTURE_2D, textureIndex);

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

void Texture::CreateBuffer(const void *data, GLsizei dataSize, const void *index, GLsizei indexSize)
{
	GLuint tempIndex;
	buffer.dataSize = dataSize;
	buffer.indexSize = indexSize;

	glGenBuffers(1, &tempIndex); // Returns a list of integers that are not currently used as buffer names.
	glBindBuffer(GL_ARRAY_BUFFER, tempIndex); // Buffer created on bind.
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	buffer.arrayLocation = tempIndex;

	glGenBuffers(1, &tempIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, index, GL_STATIC_DRAW);
	buffer.elementArrayLocation = tempIndex;
}

void Texture::Draw()
{
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glBindBuffer(GL_ARRAY_BUFFER, buffer.arrayLocation);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.elementArrayLocation);
}

//void Texture::DestroyTexture(GLuint index)
//{
//	glDeleteTextures(1, &index);
//}