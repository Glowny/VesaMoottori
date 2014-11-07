#include "Texture.h"

Texture::Texture(Image *image, vector2f position, float scale)
{
	this->image = image;
	(this->scale) = scale;
	(this->position) = position;

	//indexData[6] = { 0, 1, 2, 0, 2, 3 };
	int index[6] = { 0, 1, 2, 0, 2, 3 }; // Indexit neliölle.
	for (unsigned i = 0; i < 6; ++i)
		indexData[i] = index[i];

	// PositionX PositionY TextureX TextureY
	//GLfloat* vertex = new GLfloat[16]; // Dynaamisesti vertex datat.
	GLfloat data[28] = {
		0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 
		1.0f, 1.0f,
		
		0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 
		1.0f, 0.0f};

	for(unsigned i = 0; i < 28; ++i) // Alustetaan array.
		vertexData[i] = data[i];
	//vertexData = vertex; // Annettaan lokaatio luokalle.

	SetPosition(position);

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
	CreateBuffer(vertexData, sizeof(vertexData), indexData, sizeof(indexData));
	//glBindTexture(GL_TEXTURE_2D, 0u);
}

void Texture::SetPosition(vector2f position)
{
	vertexData[0] = position.x;
	vertexData[1] = position.y;
	vertexData[7] = position.x;
	vertexData[8] = position.y + scale;
	vertexData[14] = position.x + scale;
	vertexData[15] = position.y + scale;
	vertexData[21] = position.x + scale;
	vertexData[22] = position.y;
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