#pragma once
#include <vector>
#include "vector2.h"
#include "GL\glew.h"
#include "Texture.h"

// Tuukka: Kommentoi osaa koodia pois käytöstä että saan vaan testattua perustoimintoja.
// Esimerkiksi origot ja sourcen voi tehdä myöhemmin lisäfeatureina.

class Sprite
{
	friend class SpriteBatch;

public:
	Sprite();
	Sprite(Texture *texture);
	~Sprite();

	void SetTexture(Texture *texture);
	void SetPosition(vector2i);
	void SetSize(vector2i);
	void SetColor(float red, float green, float blue);

	vector2i GetSize();
	vector2i GetPosition();

	//vector2f GetTextureSize();
	//void SetSourceRPosition(vector2f position);
	//vector2f GetSourceRPosition();
	//void SetSourceRSize(vector2f size);
	//vector2f GetSourceRSize();
	//void SetOrigin(vector2f origin);
	//vector2f GetOrigin();
	//void SetColorRGB(float red, float blue, float green);
	//float getColorR();
	//float getColorG();
	//float getColorB();

private:
	void Draw(GLuint arrayBuffer, GLuint elementArrayBuffer);
	void ChangePositionData(); // Muuttaa verteksejä position ja koon mukaan.
	void ChangeColorData();
	void CreateIndexData(); // Alustaa indeksit.
	void CreateTextureData(); // Sprite on aina nelikulmio.
	
	bool GetTextureSet();
	bool GetSizeSet();

	Texture *texture;
	vector2i position;
	vector2i size;
	GLfloat red, green, blue;
	bool sizeSet;
	bool textureSet;

	GLfloat VERTEX_DATA[28];
	GLuint INDEX_DATA[6];

	//void ChangePositionData(vector2f windowSize);
	//void ChangeTexturePosition();
	//vector2f ToGLCoord(float x, float y);
	//GLsizei GetIndexSize();
	//GLsizei GetVertexSize();
	//GLfloat* GetVertexPointer();
	//GLuint* GetIndexPointer();
	//bool colorChanged;
	//bool positionChanged;
	//vector2f origin;
	//vector2f sourceRectSize;
	//vector2f sourceRectPosition;
	//GLfloat *vertexData;
	//GLuint *indexData;
};

