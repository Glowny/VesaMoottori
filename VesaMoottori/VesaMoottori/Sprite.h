#pragma once
#include <vector>
#include "vector2.h"
#include "GL\glew.h"
#include "Texture.h"

class Sprite
	
{
	friend class SpriteBatch;
public:
	Sprite();
	~Sprite() {};

<<<<<<< HEAD
private:
	//void Draw(GLuint arrayBuffer, GLuint elementArrayBuffer);
	void ChangePositionData(); // Muuttaa verteksej‰ position ja koon mukaan.
	void ChangeColorData();
	void CreateIndexData(); // Alustaa indeksit.
	void CreateTextureData(); // Sprite on aina nelikulmio.
	
	bool GetTextureSet();
	bool GetSizeSet();
	GLfloat* GetVertexData();
	GLuint* GetIndexData();
	GLsizei GetIndexSize();
	GLsizei GetVertexSize();
=======
	void setTexture(Texture *tex);
	vector2f getTextureSize();

	void setPosition(vector2f);
	vector2f getPosition();

	void setSourceRPosition(vector2f position);
	vector2f getSourceRPosition();

	void setSourceRSize(vector2f size);
	vector2f getSourceRSize();

	void setOrigin(vector2f origin);
	vector2f getOrigin();
	
	void setColorRGB(float red, float blue, float green);
>>>>>>> parent of 6d13cfe... Backup I

	void Draw()
	{
		texture->Draw();
	}
	float getColorR();
	float getColorG();
	float getColorB();

	void changeVertexData(); // vanha, kaikki muutetaan.
	void createIndexData(); // luo kulmasonnan

	GLsizei getIndexSize();
	GLsizei getVertexSize();
	GLfloat* getVertexPointer();
	GLuint* getIndexPointer();

private:
	vector2f ToGLCoord(float x, float y);


	Texture *texture;
	// n‰‰ on jotai kummajasia
	GLfloat *vertexData;
	GLuint *indexData;
	//
	vector2f position;
	vector2f origin;
	vector2f size;
	GLfloat red, blue, green;
	vector2f sourceRectSize;
	vector2f sourceRectPosition;
	GLfloat VERTEX_DATA[28];
	GLuint INDEX_DATA[6];

<<<<<<< HEAD
	//void ChangePositionData(vector2f windowSize);
	//void ChangeTexturePosition();
	//vector2f ToGLCoord(float x, float y);

	//GLfloat* GetVertexPointer();
	//GLuint* GetIndexPointer();
	//bool colorChanged;
	//bool positionChanged;
	//vector2f origin;
	//vector2f sourceRectSize;
	//vector2f sourceRectPosition;
	//GLfloat *vertexData;
	//GLuint *indexData;
=======
	bool colorChanged;
	bool positionChanged;
	bool texturePositionChanged;
	void changePositionData(vector2f windowSize);
	void changeColorData();
	void changeTexturePosition();


>>>>>>> parent of 6d13cfe... Backup I
};

