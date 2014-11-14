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
	position = position;
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
	//Nimet saattaa olla vähä vitullaa.
	vector2f topLeft = ToGLCoord(sourceRectPosition.x, sourceRectPosition.y);
	vector2f bottomLeft = ToGLCoord(sourceRectPosition.x, sourceRectPosition.y + sourceRectSize.y);
	vector2f topRight = ToGLCoord(sourceRectPosition.x + sourceRectSize.x, sourceRectPosition.y);
	vector2f bottomRight = ToGLCoord(sourceRectPosition.x + sourceRectSize.x, sourceRectPosition.y + sourceRectSize.y);
	// kai ne menee oikein. EI TAKUITA MYÖNNETÄ
	// sitten pitäs repiä jossakin välissä osiin, ettei KAIKKEA tarvi päivittää yhtä osaa (kuten väriä) muuttaessa,
	GLfloat vertex[] = 
	{
		position.x - origin.x, position.y - origin.y,
		red, blue, green,
		topLeft.x, topLeft.y,	

		position.x - origin.x, position.y - origin.y + size.y,
		red, blue, green,
		bottomLeft.x, bottomLeft.y,

		position.x - origin.x + size.x, position.y - origin.y,
		red, blue, green,
		topRight.x, topRight.y,

		position.x - origin.x + size.x, position.y - origin.y + size.y,
		red, blue, green,
		bottomRight.x, bottomRight.y
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
}

// Tämänkin toteutus spritebatchissa vai olikohan joku mahtisyy ettei?
vector2f Sprite::ToGLCoord(float x, float y)
{
	vector2f temp;
	temp.x = (2 * x / size.x);
	temp.y = (2 * y / size.y);
	return temp;
}

