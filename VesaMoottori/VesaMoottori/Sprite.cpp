#include "Sprite.h"

Sprite::Sprite()
{
	// SpriteBatchissa tehdään muutokset opengl koordinaatteihin (-1 - 1).
	// Tähän annetaan pikselikoordinaatit.
	texture = NULL;
	position = vector2i(0.0f, 0.0f);
	red = 1.0f;
	green = 1.0f;
	blue = 1.0f;
	sizeSet = false;
	textureSet = false;
	CreateIndexData();
	CreateTextureData();

	//sourceRectPosition = vector2f(0.0f, 0.0f);
	//origin = vector2f(0.0f, 0.0f);
	//vertexData = NULL;
	//indexData = NULL;
	//sourceRectSize.x = 0.0f;
	//sourceRectSize.y = 0.0f;
}

Sprite::Sprite(Texture *texture)
{
	texture = texture;
	position = vector2i(0.0f, 0.0f);
	red = 1.0f;
	green = 1.0f;
	blue = 1.0f;
	sizeSet = false;
	textureSet = true;
	CreateIndexData();
	CreateTextureData();
	ChangePositionData();
}

void Sprite::SetTexture(Texture *texture)
{
	(this->texture) = texture;
	textureSet = true;
	if(!sizeSet)
	{
		size = texture->GetSize();
		ChangePositionData();
		sizeSet = true;
	}
	//sourceRectSize = tex->GetSize(); // Tekstuurilla ei ole kokoa.
	//size = tex->GetSize();
	//texturePositionChanged = true;
	//ChangeVertexData();
}

void Sprite::SetPosition(vector2i position)
{
	(this->position) = position;
	ChangePositionData();
}

void Sprite::SetSize(vector2i size)
{
	(this->size) = size;
	ChangePositionData();
	sizeSet = true;
}

void Sprite::SetColor(float red, float green, float blue)
{
	(this->red) = red;
	(this->green) = green;
	(this->blue) = blue;
	ChangeColorData();
}

vector2i Sprite::GetSize()
{
	return size;
}

vector2i Sprite::GetPosition()
{
	return position;
}

void Sprite::Draw(GLuint arrayBuffer, GLuint elementArrayBuffer)
{
	glBindTexture(GL_TEXTURE_2D, (texture->GetIndex()));
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBuffer);
}

void Sprite::ChangePositionData()
{
	VERTEX_DATA[0] = (float)position.x;
	VERTEX_DATA[1] = (float)position.y;

	VERTEX_DATA[0 + 7] = (float)position.x;
	VERTEX_DATA[1 + 7] = (float)position.y + (float)size.y;

	VERTEX_DATA[0 + 14] = (float)position.x + (float)size.x;
	VERTEX_DATA[1 + 14] = (float)position.y + (float)size.y;

	VERTEX_DATA[0 + 21] = (float)position.x + (float)size.x;
	VERTEX_DATA[1 + 21] = (float)position.y;
}

void Sprite::ChangeColorData()
{
	VERTEX_DATA[2] = red;
	VERTEX_DATA[3] = green;
	VERTEX_DATA[4] = blue;

	VERTEX_DATA[2 + 7] = red;
	VERTEX_DATA[3 + 7] = green;
	VERTEX_DATA[4 + 7] = blue;

	VERTEX_DATA[2 + 14] = red;
	VERTEX_DATA[3 + 14] = green;
	VERTEX_DATA[4 + 14] = blue;

	VERTEX_DATA[2 + 21] = red;
	VERTEX_DATA[3 + 21] = green;
	VERTEX_DATA[4 + 21] = blue;
}

void Sprite::CreateIndexData()
{
	GLuint index[] = {0, 1, 2, 0, 2, 3};

	for(unsigned int i = 0; i < 6; ++i)
		INDEX_DATA[i] = index[i];
}

void Sprite::CreateTextureData()
{
	VERTEX_DATA[5] = -1.0f;
	VERTEX_DATA[6] = -1.0f;

	VERTEX_DATA[5 + 7] = -1.0f;
	VERTEX_DATA[6 + 7] = 1.0f;

	VERTEX_DATA[5 + 14] = 1.0f;
	VERTEX_DATA[6 + 14] = 1.0f;

	VERTEX_DATA[5 + 21] = 1.0f;
	VERTEX_DATA[6 + 21] = -1.0f;
}

bool Sprite::GetTextureSet()
{
	return textureSet;
}

bool Sprite::GetSizeSet()
{
	return sizeSet;
}

Sprite::~Sprite()
{
}

/*
void Sprite::ChangePositionData(vector2f windowSize)
{
	vector2f GLsize;
	GLsize.x = (size.x / windowSize.x) - 1;	// Väliaikainen, siirrettävä spritebatchiin joka tietää windowin koon.
	GLsize.y = (size.y / windowSize.y) - 1;

	VERTEX_DATA[0] = position.x - origin.x;
	VERTEX_DATA[1] = position.y - origin.y;

	VERTEX_DATA[0 + 7] = position.x - origin.x;
	VERTEX_DATA[1 + 7] = position.y - origin.y + GLsize.y;

	VERTEX_DATA[0 + 14] = position.x - origin.x - GLsize.x;
	VERTEX_DATA[1 + 14] = position.y - origin.y;

	VERTEX_DATA[0 + 21] = position.x - origin.x - GLsize.x;
	VERTEX_DATA[1 + 21] = position.y - origin.y + GLsize.y;

	//positionChanged = false;
}

void Sprite::ChangeVertexData()
{
	vector2f topLeft = ToGLCoord(sourceRectPosition.x, sourceRectPosition.y);
	vector2f bottomLeft = ToGLCoord(sourceRectPosition.x, sourceRectPosition.y + sourceRectSize.y);
	vector2f topRight = ToGLCoord(sourceRectPosition.x + sourceRectSize.x, sourceRectPosition.y);
	vector2f bottomRight = ToGLCoord(sourceRectPosition.x + sourceRectSize.x, sourceRectPosition.y + sourceRectSize.y);
	vector2f GLsize;
	GLsize.x = ( size.x / 800)-1;
	GLsize.y = ( size.y / 800)-1;

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

	// Ei pakosta tarvita.
	//texture->CreateBuffer(vertex, sizeof(vertex), INDEX_DATA, 6*4);
}

vector2f Sprite::ToGLCoord(float x, float y) // Tämänkin toteutus spritebatchissa jottei liiku välillä dataa joista osa väärässä muodossa.
{
	vector2f temp;
	temp.x = (x / size.x);
	temp.y = (y / size.y);
	return temp;
}

GLsizei Sprite::GetIndexSize()
{
	return 6; // Jossakin voisi olla joko spritessä tai tekstuurissa tallessa kuinka tämän koko, samoin verteksin.
}
GLsizei Sprite::GetVertexSize()
{
	return 28;
}

GLfloat* Sprite::GetVertexPointer()
{
	return VERTEX_DATA;
}

GLuint* Sprite::GetIndexPointer()
{
	return INDEX_DATA;
}

void Sprite::ChangeTexturePosition()
{
	vector2f topLeft = ToGLCoord(sourceRectPosition.x, sourceRectPosition.y);
	vector2f bottomLeft = ToGLCoord(sourceRectPosition.x, sourceRectPosition.y + sourceRectSize.y);
	vector2f topRight = ToGLCoord(sourceRectPosition.x + sourceRectSize.x, sourceRectPosition.y);
	vector2f bottomRight = ToGLCoord(sourceRectPosition.x + sourceRectSize.x, sourceRectPosition.y + sourceRectSize.y);

	VERTEX_DATA[5] = topLeft.x;
	VERTEX_DATA[6] = topLeft.y;

	VERTEX_DATA [5+7] = bottomLeft.x;
	VERTEX_DATA [6+7] = bottomLeft.y;

	VERTEX_DATA [5+14] = topRight.x;
	VERTEX_DATA [6+14] = topRight.y;

	VERTEX_DATA [5+21] = bottomRight.x;
	VERTEX_DATA [6+21] = bottomRight.y;
}

vector2f Sprite::getTextureSize()
{
	return texture->GetSize();
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
*/