#include "Sprite.h"

Sprite::Sprite()
{
	texture = NULL;
	vertexData = NULL;
	indexData = NULL;
	position = vector2f(0.0f, 0.0f);
	origin = vector2f(0.0f, 0.0f);
	red = 1.0f;
	blue = 1.0f;
	green = 1.0f;
}

/*Sprite::Sprite()
{
	sourceRectSize.x = 0.0f;
	sourceRectSize.y = 0.0f;
	position = vector2f(0.0f, 0.0f);
	sourceRectPosition = vector2f(0.0f, 0.0f);
	origin = vector2f(0.0f, 0.0f);
	red = 1.0f; blue = 1.0f; green = 1.0f;
}

void Sprite::setImage(Image *img)
{
	_image = *img;
	_sourceRectSize.x = image.width;
	_sourceRectSize.y = image.height;
}

std::vector<unsigned char> Sprite::getTexture()
{
	return _image.decodedImage;
}

vector2f Sprite::getTextureSize()
{
	vector2f size(_image.width, _image.height);
	return size;
}

void Sprite::setPosition(vector2f position)
{
	_position = position;
}
vector2f Sprite::getPosition()
{
	return position;
}

void Sprite::setSourceRPosition(vector2f position)
{
	sourceRectPosition = position;
}
vector2f Sprite::getSourceRPosition()
{
	return sourceRectPosition;
}

void Sprite::setSourceRSize(vector2f size)
{
	sourceRectSize = size;
}
vector2f Sprite::getSourceRSize()
{
	return sourceRectSize;
}

void Sprite::setOrigin(vector2f origin)
{
	this->origin = origin;
}

vector2f Sprite::getOrigin()
{
	return origin;
}

void Sprite::setColorRGB(float red, float blue, float green)
{
	this->red = red;
	this->blue = blue;
	this->green = green;
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

GLfloat* Sprite::getVertexData()
{	
	//croppaus oisko mit‰‰
	GLfloat vertex[] = 
	{
		position.x - origin.x, position.y - origin.y,
		red, blue, green,
		0.0f, -1.0f,

		position.x - origin.x, position.y - origin.y + 0.8f,
		red, blue, green,
		0.0f, 0.0f,

		position.x + 0.8f - origin.x, position.y + 0.8f - origin.y,
		red, blue, green,
		1.0f, 0.0f,

		position.x + 0.8f - origin.x, position.y - origin.y,
		red, blue, green,
		1.0f, -1.0f
	};

	for (unsigned i = 0; i < 28; ++i)
		VERTEX_DATA[i] = vertex[i];

	return &VERTEX_DATA[0];
}

GLuint* Sprite::getIndexData()
{

	GLuint index [] =
	{ 0, 1, 2, 0, 2, 3 };

	for (unsigned i = 0; i < 6; ++i)
		INDEX_DATA[i] = index[i];

	return &INDEX_DATA [0];
}*/