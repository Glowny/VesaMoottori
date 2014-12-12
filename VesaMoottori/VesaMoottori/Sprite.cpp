#include "Sprite.h"

Sprite::Sprite()
{
	// Tähän annetaan pikselikoordinaatit.
	texture = NULL;
	sourceRectSize.x = 0.0f;
	sourceRectSize.y = 0.0f;
	position = vector2f(0.0f, 0.0f);
	sourceRectPosition = vector2f(0.0f, 0.0f);
	origin = vector2f(0.0f, 0.0f);
	red = 255.0f; blue = 255.0f; green = 255.0f;
	createIndexData();
	changeColorData();
	changeTexturePositionData();
}

void Sprite::setTexture(Texture *tex)
{
	texture = tex;
	sourceRectSize = tex->GetSize();
	size = tex->GetSize();
	texturePositionChanged = true;
	positionChanged = true;
}

vector2f Sprite::getTextureSize()
{
	return texture->GetSize();
}

void Sprite::setPosition(vector2f position)
{
	this->position = position;
	positionChanged = true;
}

vector2f Sprite::getPosition()
{
	return position;
}

void Sprite::setSourceRPosition(vector2f position)
{
	sourceRectPosition = position;
	texturePositionChanged = true;
}

vector2f Sprite::getSourceRPosition()
{
	return sourceRectPosition;
}

void Sprite::setSourceRSize(vector2f size)
{
	sourceRectSize = size;
	texturePositionChanged = true;
}

vector2f Sprite::getSourceRSize()
{
	return sourceRectSize;
}

void Sprite::setOrigin(vector2f origin)
{
	this->origin = origin;
	positionChanged = true;
}

vector2f Sprite::getOrigin()
{
	return origin;
}

void Sprite::setSize(vector2f size)
{
	sourceRectSize = vector2f((sourceRectSize.x / this->size.x)*size.x, (sourceRectSize.y / this->size.y)*size.y);
	this->size = size;
	positionChanged = true;
	texturePositionChanged = true;
}

vector2f Sprite::getSize()
{
	return size;
}

void Sprite::setColorRGB(float red, float blue, float green)
{
	this->red = red;
	this->blue = blue;
	this->green = green;
	colorChanged = true;
}

float Sprite::getColorR()
{
	return red;
}

float Sprite::getColorG()
{
	return green;
}

float Sprite::getColorB()
{
	return blue;
}

void Sprite::changePositionData()
{
	VERTEX_DATA[0] = position.x + origin.x;
	VERTEX_DATA[1] = position.y - origin.y;

	VERTEX_DATA[0 + 7] = position.x + origin.x;
	VERTEX_DATA[1 + 7] = position.y - origin.y + size.y;

	VERTEX_DATA[0 + 14] = position.x + origin.x - size.x;
	VERTEX_DATA[1 + 14] = position.y - origin.y;

	VERTEX_DATA[0 + 21] = position.x + origin.x - size.x;
	VERTEX_DATA[1 + 21] = position.y - origin.y + size.y;

	positionChanged = false;
}

void Sprite::changeColorData()
{
	VERTEX_DATA[2] = red;
	VERTEX_DATA[3] = blue;
	VERTEX_DATA[4] = green;

	VERTEX_DATA[2 + 7] = red;
	VERTEX_DATA[3 + 7] = blue;
	VERTEX_DATA[4 + 7] = green;

	VERTEX_DATA[2 + 14] = red;
	VERTEX_DATA[3 + 14] = blue;
	VERTEX_DATA[4 + 14] = green;

	VERTEX_DATA[2 + 21] = red;
	VERTEX_DATA[3 + 21] = blue;
	VERTEX_DATA[4 + 21] = green;

	colorChanged = false;
}

void Sprite::changeTexturePositionData()
{
	vector2f topLeft(sourceRectPosition.x, sourceRectPosition.y);
	vector2f bottomLeft(sourceRectPosition.x, sourceRectPosition.y + sourceRectSize.y);
	vector2f topRight(sourceRectPosition.x + sourceRectSize.x, sourceRectPosition.y);
	vector2f bottomRight(sourceRectPosition.x + sourceRectSize.x, sourceRectPosition.y + sourceRectSize.y);

	VERTEX_DATA[5] = topLeft.x;
	VERTEX_DATA[6] = topLeft.y;

	VERTEX_DATA[5 + 7] = bottomLeft.x;
	VERTEX_DATA[6 + 7] = bottomLeft.y;

	VERTEX_DATA[5 + 14] =  topRight.x;
	VERTEX_DATA[6 + 14] = topRight.y;

	VERTEX_DATA[5 + 21] =  bottomRight.x;
	VERTEX_DATA[6 + 21] =  bottomRight.y;

	texturePositionChanged = false;
}

void Sprite::createIndexData()
{
	GLuint index [] = { 0, 1, 2, 1, 2, 3 }; // Nelikulmio.
	
	for (unsigned i = 0; i < 6; ++i)
		INDEX_DATA[i] = index[i];
}

GLsizei Sprite::getIndexSize()
{
	return 6; // Moottorilla voi tehdä vain neliöitä \o/
}

GLsizei Sprite::getVertexSize()
{
	return 28;
}

GLfloat* Sprite::getVertexPointer()
{
	return VERTEX_DATA;
}

GLuint* Sprite::getIndexPointer()
{
	return INDEX_DATA;
}