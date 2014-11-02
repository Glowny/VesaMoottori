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
	_sourceRectSize.x = 0.0f;
	_sourceRectSize.y = 0.0f;
	_position = vector2f(0.0f, 0.0f);
	_sourceRectPosition = vector2f(0.0f, 0.0f);
	_origin = vector2f(0.0f, 0.0f);
	_red = 1.0f; _blue = 1.0f; _green = 1.0f;
}

void Sprite::setImage(Image *img)
{
	_image = *img;
	_sourceRectSize.x = _image.width;
	_sourceRectSize.y = _image.height;
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
	return _position;
}

void Sprite::setSourceRPosition(vector2f position)
{
	_sourceRectPosition = position;
}
vector2f Sprite::getSourceRPosition()
{
	return _sourceRectPosition;
}

void Sprite::setSourceRSize(vector2f size)
{
	_sourceRectSize = size;
}
vector2f Sprite::getSourceRSize()
{
	return _sourceRectSize;
}

void Sprite::setOrigin(vector2f origin)
{
	_origin = origin;
}

vector2f Sprite::getOrigin()
{
	return _origin;
}

void Sprite::setColorRGB(float red, float blue, float green)
{
	_red = red;
	_blue = blue;
	_green = green;
}

float Sprite::getColorR()
{
	return _red;
}

float Sprite::getColorG()
{
	return _green;
}

float Sprite::getColorB()
{
	return _blue;
}

GLfloat* Sprite::getVertexData()
{	
	//croppaus oisko mit‰‰
	GLfloat vertex[] = 
	{
		_position.x - _origin.x, _position.y - _origin.y,
		_red, _blue, _green,
		0.0f, -1.0f,

		_position.x - _origin.x, _position.y - _origin.y + 0.8f,
		_red, _blue, _green,
		0.0f, 0.0f,

		_position.x + 0.8f - _origin.x, _position.y + 0.8f - _origin.y,
		_red, _blue, _green,
		1.0f, 0.0f,

		_position.x + 0.8f - _origin.x, _position.y - _origin.y,
		_red, _blue, _green,
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