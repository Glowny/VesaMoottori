#include "Sprite.h"


Sprite::Sprite(std::vector<unsigned char> decodedTexture, vector2i textureSize)
{
	_texture = decodedTexture;
	_textureSize = textureSize;
	_position = vector2i(0, 0);
	_sourceRectSize = _textureSize;
	_sourceRectPosition = vector2i(0, 0);
	_origin = vector2i(0, 0);
	_red = 1.0f; _blue = 1.0f; _green = 1.0f;
}

std::vector<unsigned char> Sprite::getTexture()
{
	return _texture;
}
vector2i Sprite::getTextureSize()
{
	return _textureSize;
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

	GLfloat AVERTEX_DATA[28] =
	{
		_position.x, _position.y,
		_red, _blue, _green,
		0.0f, -1.0f,

		_position.x, _position.y + _sourceRectSize.y,
		_red, _blue, _green,
		0.0f, 0.0f,

		_sourceRectSize.x + _position.x, _sourceRectSize.y + _position.y,
		_red, _blue, _green,
		1.0f, 0.0f,

		_sourceRectSize.x + _position.x, _position.y,
		_red, _blue, _green,
		1.0f, -1.0f
	};
	for (int i = 0; i < 28; i++)
	{
		VERTEX_DATA[i] = AVERTEX_DATA[i];
	}
	return &VERTEX_DATA[0];
}


Sprite::~Sprite()
{

}
