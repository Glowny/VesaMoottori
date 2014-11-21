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
	// SpriteBatchissa tehd‰‰n muutokset opengl koordinaatteihin (-1 - 1)
	// T‰h‰n annetaan pikselikoordinaatit
	texture = NULL;
	vertexData = NULL;
	indexData = NULL;
	sourceRectSize.x = 0.0f;
	sourceRectSize.y = 0.0f;
	position = vector2f(0.0f, 0.0f);
	sourceRectPosition = vector2f(0.0f, 0.0f);
	origin = vector2f(0.0f, 0.0f);
	red = 1.0f; blue = 1.0f; green = 1.0f;
}

void Sprite::setTexture(Texture *tex)
{
	texture = tex;
	sourceRectSize = tex->GetSize();
	size = tex->GetSize();
}


vector2f Sprite::getTextureSize()
{
	return texture->GetSize();
}

void Sprite::setPosition(vector2f position)
{
	this->position = position;
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

GLfloat* Sprite::createVertexData()
{
	//Nimet saattaa olla v‰h‰ vitullaa.
	vector2f topLeft = ToGLCoord(sourceRectPosition.x, sourceRectPosition.y);
	vector2f bottomLeft = ToGLCoord(sourceRectPosition.x, sourceRectPosition.y + sourceRectSize.y);
	vector2f topRight = ToGLCoord(sourceRectPosition.x + sourceRectSize.x, sourceRectPosition.y);
	vector2f bottomRight = ToGLCoord(sourceRectPosition.x + sourceRectSize.x, sourceRectPosition.y + sourceRectSize.y);
	vector2f GLsize;
	GLsize.x = ( size.x / 800)-1;	// v‰liaikainen, siirrett‰v‰ spritebatchiin joka tiet‰‰ windowin koon.
	GLsize.y = ( size.y / 800)-1;
	// jos tehd‰‰n spritebatchissa:
	/*vector2f topLeft(sourceRectPosition.x, sourceRectPosition.y);
	vector2f bottomLeft(sourceRectPosition.x, sourceRectPosition.y + sourceRectSize.y);
	vector2f topRight(sourceRectPosition.x + sourceRectSize.x, sourceRectPosition.y);
	vector2f bottomRight(sourceRectPosition.x + sourceRectSize.x, sourceRectPosition.y + sourceRectSize.y);*/

	// sitten pit‰s repi‰ jossakin v‰liss‰ osiin, ettei KAIKKEA tarvi p‰ivitt‰‰ yht‰ osaa (kuten v‰ri‰) muuttaessa,
	GLfloat vertex[] = 
	{
		position.x - origin.x, position.y - origin.y,
		red, blue, green,
		topLeft.x, topLeft.y,	

		position.x - origin.x, position.y - origin.y + GLsize.y,
		red, blue, green,
		bottomLeft.x, bottomLeft.y,

		position.x - origin.x - GLsize.x, position.y - origin.y,
		red, blue, green,
		topRight.x, topRight.y,

		position.x - origin.x - GLsize.x, position.y - origin.y + GLsize.y,
		red, blue, green,
		bottomRight.x, bottomRight.y
	};

	for (unsigned i = 0; i < 28; ++i)
		VERTEX_DATA[i] = vertex[i];

	// ei pakosta tarvita
	texture->CreateBuffer(vertex, sizeof(vertex), getIndexData(), 6*4);
	return &VERTEX_DATA[0];
}

GLuint* Sprite::getIndexData()
{
	//nelikulmio
	GLuint index [] =
	{ 0, 1, 2, 1, 2, 3 };

	for (unsigned i = 0; i < 6; ++i)
		INDEX_DATA[i] = index[i];

	return &INDEX_DATA [0];
}

// T‰m‰nkin toteutus spritebatchissa jottei liiku v‰lill‰ dataa joista osa v‰‰r‰ss‰ muodossa
vector2f Sprite::ToGLCoord(float x, float y)
{
	vector2f temp;
	temp.x = (1 * x / size.x);
	temp.y = (1 * y / size.y);
	return temp;
}

GLsizei Sprite::getIndexSize()
{
	return 6;		// jossakin voisi olla joko spritess‰ tai tekstuurissa tallessa kuinka t‰m‰n koko, samoin verteksin
}
GLsizei Sprite::getVertexSize()
{
	return 28;
}

GLfloat* Sprite::getVertexPointer()
{
	return vertexData;
}
GLuint* Sprite::getIndexPointer()
{
	return indexData;
}