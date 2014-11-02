#pragma once
#include <vector>
#include "vector2.h"
#include "GL\glew.h"
#include "Texture.h"

class Sprite
{
public:
	Sprite();
	~Sprite() {};

	/*void setImage(Image *img);
	std::vector<unsigned char> getTexture();
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

	float getColorR();
	float getColorG();
	float getColorB();

	GLfloat* getVertexData();
	GLuint* getIndexData();*/

private:
	Texture *texture;
	GLfloat *vertexData;
	GLuint *indexData;
	vector2f position;
	vector2f origin;
	GLfloat red, blue, green;

	/*vector2f sourceRectSize;
	vector2f sourceRectPosition;
	GLfloat VERTEX_DATA[28];
	GLuint INDEX_DATA[6];*/
};

