#include "Sprite.h"


Sprite::Sprite(Image img)
{
	_position = vector2i(0, 0);
	_sourceRectSize = _textureSize;
	_sourceRectPosition = vector2i(0, 0);
	_origin = vector2i(0, 0);
	_red = 1.0f; _blue = 1.0f; _green = 1.0f;
}

std::vector<unsigned char> Sprite::getTexture()
{
	return _image.decodedImage;
}
vector2i Sprite::getTextureSize()
{
	vector2i size(_image.width, _image.height);
	return size;
}

void Sprite::setPosition(vector2i position)
{
	_position = position;
}
vector2i Sprite::getPosition()
{
	return _position;
}

void Sprite::setSourceRPosition(vector2i position)
{
	_sourceRectPosition = position;
}
vector2i Sprite::getSourceRPosition()
{
	return _sourceRectPosition;
}

void Sprite::setSourceRSize(vector2i size)
{
	_sourceRectSize = size;
}
vector2i Sprite::getSourceRSize()
{
	return _sourceRectSize;
}

void Sprite::setOrigin(vector2i origin)
{
	_origin = origin;
}

vector2i Sprite::getOrigin()
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
	return _blue;
}
float Sprite::getColorB()
{
	return _green;
}

GLfloat* Sprite::getVertexData()
{
	// nelikulmioita vain piirrett‰v‰n‰ atm. T‰h‰n setteri? Jostakin pit‰‰ saada koko-tiedot.
	GLfloat AVERTEX_DATA[28] =
	{
		_position.x-_origin.x, _position.y-_origin.y,
		_red, _blue, _green,
		0.0f, -1.0f,

		_position.x-_origin.x, _position.y-_origin.y + _sourceRectSize.y,
		_red, _blue, _green,
		0.0f, 0.0f,

		_position.x + _sourceRectSize.x - _origin.x, _position.y + _sourceRectSize.y - _origin.y,
		_red, _blue, _green,
		1.0f, 0.0f,

		_position.x + _sourceRectSize.x - _origin.x, _position.y - _origin.y,
		_red, _blue, _green,
		1.0f, -1.0f
	};
	for (int i = 0; i < 28; i++)
	{
		VERTEX_DATA[i] = AVERTEX_DATA[i];
	}
	return &VERTEX_DATA[0];
}
GLfloat* Sprite::getIndexData()
{
	GLfloat AINDEX_DATA [] = { 0, 1, 2, 0, 2, 3 };	// Nelikulmio piirrettyn‰ kahdella kolmiolla, kustomoitavissa t‰m‰, esim setteri?
	for (int i = 0; i < 6; i++)
	{
		INDEX_DATA[i] = AINDEX_DATA[i];
	}
	return INDEX_DATA;
}

Sprite::~Sprite()
{

}
