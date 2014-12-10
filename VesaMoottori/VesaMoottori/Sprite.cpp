#include "Sprite.h"

//Sprite::Sprite()
//{
//	texture = NULL;
//	vertexData = NULL;
//	indexData = NULL;
//	position = vector2f(0.0f, 0.0f);
//	origin = vector2f(0.0f, 0.0f);
//	red = 1.0f;
//	blue = 1.0f;
//	green = 1.0f;
//}

Sprite::Sprite()
{
	// SpriteBatchissa tehdään muutokset opengl koordinaatteihin (-1 - 1)
	// Tähän annetaan pikselikoordinaatit
	texture = NULL;
	vertexData = NULL;
	indexData = NULL;
	sourceRectSize.x = 0.0f;
	sourceRectSize.y = 0.0f;
	position = vector2f(0.0f, 0.0f);
	sourceRectPosition = vector2f(0.0f, 0.0f);
	origin = vector2f(0.0f, 0.0f);
	red = 255.0f; blue = 255.0f; green = 255.0f;
	createIndexData();

}

void Sprite::setTexture(Texture *tex)
{
	texture = tex;
	sourceRectSize = tex->GetSize();
	size = tex->GetSize();
	texturePositionChanged = true;
	changeVertexData();
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

void Sprite::setColorRGB(float red, float blue, float green)
{
	this->red = red;
	this->blue = blue;
	this->green = green;
	colorChanged = true;
	// DEBUGAAN SAA OTTAA POIS
	changeColorData();
	//
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
// vanha
void Sprite::changeVertexData()
{
	vector2f topLeft(sourceRectPosition.x, sourceRectPosition.y);
	vector2f bottomLeft(sourceRectPosition.x, sourceRectPosition.y + sourceRectSize.y);
	vector2f topRight(sourceRectPosition.x + sourceRectSize.x, sourceRectPosition.y);
	vector2f bottomRight(sourceRectPosition.x + sourceRectSize.x, sourceRectPosition.y + sourceRectSize.y);

	GLfloat vertex[] = 
	{
		position.x - origin.x, position.y - origin.y,
		red, blue, green,
		topLeft.x, topLeft.y,	

		position.x - origin.x, position.y - origin.y + size.y,
		red, blue, green,
		bottomLeft.x, bottomLeft.y,

		position.x - origin.x - size.x, position.y - origin.y,
		red, blue, green,
		topRight.x, topRight.y,

		position.x - origin.x - size.x, position.y - origin.y + size.y,
		red, blue, green,
		bottomRight.x, bottomRight.y
	};

	for (unsigned i = 0; i < 28; ++i)
		VERTEX_DATA[i] = vertex[i];

	// ei pakosta tarvita
	//texture->CreateBuffer(vertex, sizeof(vertex), INDEX_DATA, 6*4);
}

void Sprite::changePositionData()
{
	VERTEX_DATA[0] = position.x - origin.x;
	VERTEX_DATA[1] = position.y - origin.y;

	VERTEX_DATA[0 + 7] = position.x - origin.x;
	VERTEX_DATA[1 + 7] = position.y - origin.y + size.y;

	VERTEX_DATA[0 + 14] = position.x - origin.x - size.x;
	VERTEX_DATA[1 + 14] = position.y - origin.y;

	VERTEX_DATA[0 + 21] = position.x - origin.x - size.x;
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
void Sprite::changeTexturePosition()
{
	vector2f topLeft(sourceRectPosition.x, sourceRectPosition.y);
	vector2f bottomLeft(sourceRectPosition.x, sourceRectPosition.y + sourceRectSize.y);
	vector2f topRight(sourceRectPosition.x + sourceRectSize.x, sourceRectPosition.y);
	vector2f bottomRight(sourceRectPosition.x + sourceRectSize.x, sourceRectPosition.y + sourceRectSize.y);

	VERTEX_DATA[5] = topLeft.x;
	VERTEX_DATA[6] = topLeft.y;

	VERTEX_DATA [5+7] = bottomLeft.x;
	VERTEX_DATA [6+7] = bottomLeft.y;

	VERTEX_DATA [5+14] = topRight.x;
	VERTEX_DATA [6+14] = topRight.y;

	VERTEX_DATA [5+21] = bottomRight.x;
	VERTEX_DATA [6+21] = bottomRight.y;

	texturePositionChanged = false;
}

void Sprite::createIndexData()
{
	//nelikulmio
	GLuint index [] =
	{ 0, 1, 2, 1, 2, 3 };
	

	for (unsigned i = 0; i < 6; ++i)
		INDEX_DATA[i] = index[i];

}

// Tämänkin toteutus spritebatchissa jottei liiku välillä dataa joista osa väärässä muodossa

GLsizei Sprite::getIndexSize()
{
	return 6;		// jossakin voisi olla joko spritessä tai tekstuurissa tallessa kuinka tämän koko, samoin verteksin
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